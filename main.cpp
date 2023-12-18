#include "src/Log/FileLogger.h"
#include "src/Log/ConsoleLogger.h"
#include "src/Schedule.h"

int main(int argc, char** argv) {
    std::string input = "DATA_Files";
    std::string output = "result.txt";
    if (argc > 3) {
        input = std::string(argv[1]);
        output = std::string(argv[2]);
    } else {
        std::cout << "YOU'RE RUNNING PROGRAM WITHOUT ARGUMENTS, SETTING DEFAULT VALUES (DATA_Files, result.txt).\nTRY: " << argv[0] << " <input-directory> <output-file>" << std::endl;
    }
    Schedule schedule(input);
    LogObserver log_observer(&schedule);
    ConsoleLogger console_logger(&log_observer, { MessageType::INFO });
    FileLogger shooting_logger(&log_observer, output, { MessageType::SCHEDULE });
    schedule.buildSchedule();
    return 0;
}