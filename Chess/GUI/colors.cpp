#include "colors.h"

/**
 *
 * Light checkerboard
 * 
 * @return
 */
QColor Colors::light() {
    return QColor(154,204,255);

}

/**
 *  Dark checkerboard
 * 
 * @return
 */
QColor Colors::dark() {
    return QColor(0,101,159);
}

/**
 *  Background color behind game board
 * 
 * @return
 */
QColor Colors::background() {
    return QColor(153,153,153);
}

/**
 * Highlighted piece color 
 * 
 * @return
 */
QColor Colors::highlight() {
    return QColor(255,223,50);
}

/**
 *  possible move spot color
 * 
 * @return
 */
QColor Colors::move() {
    return QColor(185,255,50);
}

/**
 *  Attack piece spot
 * 
 * @return
 */
QColor Colors::special() {
    return QColor(255,50,50);
}
