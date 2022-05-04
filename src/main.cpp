#include <QApplication>

#include "tracker.hpp"

int main(int argc, char** argv){
    QApplication application(argc, argv);

    tracker widget;
    widget.show();

	return application.exec();
}
