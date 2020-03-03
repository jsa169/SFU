
#ifndef _BT_VISUALIZE_H_
#define _BT_VISUALIZE_H_

#include <vector>
#include <string>


class BTascii;


BTascii join(BTascii left, BTascii right, std::string root);


class BTascii {
	private:
	public:
		unsigned int rootcol;
		unsigned int rows;
		unsigned int cols;
		std::vector <std::string> grid;
		bool isEmpty();


		BTascii() { rows = cols = rootcol = 0; } 
		BTascii(std::string s) { grid.push_back(s); rows = 1; cols = s.length(); rootcol = cols/2; }
		~BTascii() {}

		// both left, right must be nonempty, or else the nonempty one is returned and root is not used
		friend BTascii join(BTascii left, BTascii right, std::string root);

		void display();
		friend void swap(BTascii &first, BTascii &second) {
			std::swap(first.rootcol, second.rootcol);
			std::swap(first.rows, second.rows);
			std::swap(first.cols, second.cols);
			std::swap(first.grid, second.grid);
		}
		BTascii& operator=(const BTascii& other);

};



#endif // _BT_VISUALIZE_H_
