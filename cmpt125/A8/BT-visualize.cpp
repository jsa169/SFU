#include "BT-visualize.h"

#include <vector>
#include <string>
#include <assert.h>
#include <stdio.h>



bool BTascii::isEmpty() {
    return rows == 0;
}



BTascii join(BTascii left, BTascii right, std::string root) {
    BTascii ret;
    if (left.isEmpty() && right.isEmpty()) return BTascii(root);
    int leftpad = 0;
    int midpad = 1;
    int rightpad = 0;
    int rootlen = root.length();
    char leftdot = '.';
    char rightdot = '.';
    char leftup = ':';
    char rightup = ':';
    ret.rootcol = (left.rootcol + (left.cols + midpad + right.rootcol))/2;
    if (left.isEmpty()) {
        left.rows = 1;
        left.cols = 1;
    	midpad = 0;
        left.rootcol = 0;
        leftdot = ' ';
        leftup = ' ';
        left.grid.push_back(std::string(" "));
    }
    if (right.isEmpty()) {
        right.rows = 1;
        right.cols = 1;
    	midpad = 0;
        right.rootcol = 0;
        rightdot = ' ';
        rightup = ' ';
        right.grid.push_back(std::string(" "));
    }
    int rootstartpos = ret.rootcol - rootlen/2;
    while (rootstartpos < 0) {
        leftpad++;
        rootstartpos++;
        ret.rootcol++;
    }
    ret.cols = leftpad + left.cols + midpad + right.cols + rightpad;
    while (rootstartpos + rootlen > ret.cols) {
        rightpad++;
        ret.cols++;
    }

    int parity = root.length() % 2;
    std::string mid;
    if (parity) {
        mid = std::string(":");
    } else {
        mid = std::string("::");
    }

    //ret.rows = std::max(left.rows, right.rows) + 2;
    ret.rows = std::max(left.rows, right.rows) + 3;
    ret.grid.push_back(std::string(rootstartpos, ' ') + root + std::string(ret.cols - rootlen - rootstartpos, ' '));
    ret.grid.push_back(std::string(leftpad + left.rootcol, ' ') + std::string(ret.rootcol - leftpad - left.rootcol - !parity, leftdot) + mid + std::string(leftpad + left.cols + midpad + right.rootcol - ret.rootcol, rightdot) + std::string(ret.cols - leftpad - left.cols - midpad - right.rootcol - 1, ' '));
    //ret.grid.push_back(std::string(leftpad + left.rootcol, ' ') + std::string(":") + std::string(ret.rootcol - leftpad - left.rootcol - 1, ' ') + mid + std::string(leftpad + left.cols + midpad + right.rootcol - ret.rootcol - !parity - 1, ' ') + std::string(":") + std::string(ret.cols - leftpad - left.cols - midpad - right.rootcol - 1, ' '));
    ret.grid.push_back(std::string(leftpad + left.rootcol, ' ') + std::string(1,leftup) + std::string(left.cols + midpad + right.rootcol - left.rootcol - 1, ' ') + std::string(1,rightup) + std::string(ret.cols - leftpad - left.cols - midpad - right.rootcol -1, ' '));
    //for (int i = 0; i < ret.rows - 2; i++) {
    for (int i = 0; i < ret.rows - 3; i++) {
        if (i >= left.rows) {
            assert(i < right.rows);
            ret.grid.push_back(std::string(leftpad + left.cols + midpad, ' ') + right.grid[i] + std::string(rightpad, ' '));
        } else if (i >= right.rows) {
            ret.grid.push_back(std::string(leftpad, ' ') + left.grid[i] + std::string(midpad + right.cols + rightpad, ' '));
        } else {
            ret.grid.push_back(std::string(leftpad, ' ') + left.grid[i] + std::string(midpad, ' ') +  right.grid[i] + std::string(rightpad, ' '));
        }
    }
    return ret;

}



void BTascii::display() {
    assert(rows == grid.size());
    for (int i = 0; i < rows; i++) {
        assert(cols == grid[i].length());
        puts(grid[i].c_str());
    }
}


BTascii& BTascii::operator=(const BTascii& other)
{
    BTascii temp(other);
    swap(*this, temp);

    return *this;
}
