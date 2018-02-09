// Your code here!
#include "exam.h"
#include "matrix.h"

namespace exam {
  Matrix flip_vert(const Matrix &m){
    int numRow = m.get_num_rows();
    int numCol = m.get_num_columns();
    Matrix newM(numRow, numCol);
    
    for (int i = 0; i < numRow;  i++) {
      for (int j = 0; j < numCol; j++) {
	int value = m.get_coord(i,j);
       
	newM.set_coord(i, numCol - j-1, value);
      }
    }

	return newM;
  }
}
