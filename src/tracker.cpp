#include "tracker.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>


std::string getDate()
{
    const auto now = std::chrono::system_clock::now();
    const auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d");
    return ss.str();
}

void writeTimeToFile(std::vector<long>& values) {
    const std::string subdir = "data/";
    const std::string ext = ".csv";
    std::string fileName = getDate() + "_data";

    // Check subdir exists
    if(!std::filesystem::exists(subdir)) {
        std::filesystem::create_directory(subdir);
    }
    // Check file not exist already
    if(std::filesystem::exists(subdir + fileName + ext)) {
        unsigned count = 1;

        // Try path "data/filename(count).csv"
        const std::string before = subdir + fileName + "(";
        const std::string after = ")" + ext;

        while (std::filesystem::exists(before + std::to_string(count) + after))
            ++count;

        fileName.append("(" + std::to_string(count) + ")");
    }

    std::ofstream file(subdir + fileName + ext);

    // File could be opened
    if(file.is_open()) {
        std::string buffer;
        for(const auto& val: values)
            buffer.append(std::to_string(val) + ";");

        buffer.pop_back();      // Delete last ";"
        buffer.append("\n");  // Properly newline at end

        file << buffer;
        file.close();
    }
    else {
        for(const auto& val: values)
            std::cout << val << ";";

        // TODO: Better solution than just output.
    }
}


tracker::tracker(QWidget* parent) : QWidget(parent) {
    lMain = new QVBoxLayout(this);
    lButtons = new QHBoxLayout(this);

    bStart = new QPushButton("Start", this);
    bEnd = new QPushButton("End", this);
    bTracker = new QPushButton("0", this);

    lButtons->addWidget(bStart);
    lButtons->addWidget(bEnd);

    lMain->addWidget(bTracker);
    lMain->addLayout(lButtons);

    setLayout(lMain);

    setConnections();
}

void tracker::setConnections() {
    connect(bStart, SIGNAL(clicked()), this, SLOT(start()));
    connect(bEnd, SIGNAL(clicked()), this, SLOT(end()));
    connect(bTracker, SIGNAL(clicked()), this, SLOT(trackEvent()));
}

void tracker::start() noexcept {
    if(started)
        return;

    startTime = std::chrono::system_clock::now();
    started = true;
}

void tracker::end() {
    // Export csv file
    writeTimeToFile(events);
}

void tracker::trackEvent() {
    if(!started)
        return;

    events.push_back(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - startTime).count());
    bTracker->setText(QString(std::to_string(events.size()).c_str()));
}

tracker::~tracker() noexcept {
    delete bStart;
    delete bEnd;
    delete bTracker;

    delete lButtons;
    delete lMain;
}

