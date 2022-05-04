#include "tracker.hpp"

#include <iostream> // TODO: Remove

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
    for(std::size_t i = 0; i < events.size(); i++) {
        std::cout << i << ": " << events[i] << " s \n";
    }
   // Export csv file
}

void tracker::trackEvent() {
    if(!started)
        return;
    events.push_back(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - startTime).count());
    bTracker->setText(QString(std::to_string(events.size()).c_str()));
    // add to vector current time
}

tracker::~tracker() noexcept {
    delete bStart;
    delete bEnd;
    delete bTracker;

    delete lButtons;
    delete lMain;
}



