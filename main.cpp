#include "src/Log/FileLogger.h"
#include "src/Log/ConsoleLogger.h"
#include "src/Schedule.h"

int main() {
    Schedule schedule("DATA_Files");
    LogObserver log_observer(&schedule);
    ConsoleLogger console_logger(&log_observer, { MessageType::INFO });
    FileLogger shooting_logger(&log_observer, "result.txt", { MessageType::SCHEDULE });
    schedule.buildSchedule();
    return 0;
}