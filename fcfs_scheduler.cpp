#include "fcfs_scheduler.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream> 
#include <random>

FCFS_Scheduler::FCFS_Scheduler(int cores) : num_cores(cores), running(true) {}

FCFS_Scheduler::~FCFS_Scheduler() {
    stop();
}

void FCFS_Scheduler::add_process(Process* proc) {
    std::lock_guard<std::mutex> lock(mtx);
    process_queue.push(proc);
    cv.notify_one();
    // std::cout << "Added process " << proc->name << " to the queue.\n";
}

void FCFS_Scheduler::start() {
    for (int i = 0; i < num_cores; ++i) {
        cpu_threads.emplace_back(&FCFS_Scheduler::cpu_worker, this, i);
    }
    std::cout << "Scheduler started with " << num_cores << " cores.\n";
}

void FCFS_Scheduler::stop() {
    running = false;
    cv.notify_all();
    for (auto& thread : cpu_threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    std::cout << "Scheduler stopped.\n";
}

void FCFS_Scheduler::cpu_worker(int core_id) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> exec_dist(1, 10); // Random number of commands to execute per iteration

    while (running) {
        Process* proc = nullptr;

        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&] { return !process_queue.empty() || !running; });

            if (!running && process_queue.empty()) break;

            proc = process_queue.front();
            process_queue.pop();
            proc->core_id = core_id;
            proc->start_time = std::chrono::system_clock::now();
            running_processes.push_back(proc);
        }

        while (proc->executed_commands < proc->total_commands) {
            {
                auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::tm local_tm;
                localtime_s(&local_tm, &now);
                proc->log_file << "(" << std::put_time(&local_tm, "%m/%d/%Y %I:%M:%S%p") << ") Core:" << core_id << " \"Hello world from " << proc->name << "!\"\n";

                std::lock_guard<std::mutex> lock(mtx);
                proc->executed_commands += exec_dist(gen);
                if (proc->executed_commands > proc->total_commands) {
                    proc->executed_commands = proc->total_commands;
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }

        {
            std::lock_guard<std::mutex> lock(mtx);
            running_processes.remove(proc);
            finished_processes.push_back(proc);
        }
    }
}

void FCFS_Scheduler::print_running_processes() {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Running processes:\n";
    for (auto& proc : running_processes) {
        std::cout << proc->name << " (" << proc->get_start_time() << ") Core: "
            << (proc->core_id == -1 ? "N/A" : std::to_string(proc->core_id))
            << " " << proc->executed_commands << " / " << proc->total_commands << "\n";
    }
    std::cout << "----------------\n";
}

void FCFS_Scheduler::print_finished_processes() {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Finished processes:\n";
    for (auto& proc : finished_processes) {
        std::cout << proc->name << " (" << proc->get_start_time() << ") Finished "
            << proc->executed_commands << " / " << proc->total_commands << "\n";
    }
    std::cout << "----------------\n";
}

void FCFS_Scheduler::screen_ls() {
    print_running_processes();
    print_finished_processes();
}

void FCFS_Scheduler::print_process_details(const std::string& process_name, int screen) {
    std::lock_guard<std::mutex> lock(mtx);

    std::queue<Process*> temp_queue = process_queue;
    while (!temp_queue.empty()) {
        Process* proc = temp_queue.front();
        temp_queue.pop();
        if (proc->name == process_name) {
            proc->displayProcessInfo();
            return;
        }
    }

    for (auto& proc : running_processes) {
        if (proc->name == process_name && screen == 0) {
            system("cls");
            proc->displayProcessInfo();
            return;
        }
        else if (proc->name == process_name && screen == 1) {
            proc->displayProcessInfo();
            return;
        }
    }

    for (auto& proc : finished_processes) {
        if (proc->name == process_name && screen == 1) {
            proc->displayProcessInfo();
            std::cout << "Process " << process_name << " has finished and cannot be accessed after exiting this screen.\n";
            return;
        }
        else if (proc->name == process_name && screen == 0) {
            std::cout << "Process " << process_name << " not found.\n";
            return;
        }
    }

    std::cout << "Process " << process_name << " not found.\n";
}

void FCFS_Scheduler::print_process_queue_names() {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Processes in the queue:\n";
    std::queue<Process*> temp_queue = process_queue;
    while (!temp_queue.empty()) {
        std::cout << temp_queue.front()->name << "\n";
        temp_queue.pop();
    }
    std::cout << "----------------\n";
}
