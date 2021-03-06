#include <iostream>
#include <fstream>

using namespace std;

struct newGraph 
{
    int size;
    int size_of_matrix = 2;
    bool** matrix = new bool* [size_of_matrix];

    newGraph(int size)  
    {
        for (int i = 0; i < size_of_matrix; i++)
        {
            matrix[i] = new bool[size_of_matrix];
        }
        clear();
        this->size = size;
        if (size > size_of_matrix) change_size_of_matrix (size / 2 * 3);
    }

    void change_size_of_matrix(int new_size) 
    {
        bool** new_matrix = new bool* [new_size];

        for (int i = 0; i < new_size; i++) 
        {
            new_matrix[i] = new bool[new_size];
            for (int j = 0; j < new_size; j++) 
            {
                if (i < size && j < size) new_matrix[i][j] = matrix[i][j];
                else new_matrix[i][j] = false;
            }
        }
        swap(matrix, new_matrix);
        for (int i = 0; i < size; i++)
        {
            delete[] new_matrix[i];
        }
        size_of_matrix = new_size;
    }

    void add_edge(int first, int next) 
    {
        int max;
        if (first > next) max = first;
        else max = next;
        if (max + 1 > size_of_matrix)
        {
            change_size_of_matrix((max + 1) / 2 * 3);
            size = max + 1;
        }
        matrix[first][next] = true;
    }

    void delete_edge(int first, int next)
     {
         if (first < size && next < size)
         {
             matrix[first][next] = false;
         }
     }

    void merge(int old, int in) 
     {
          for (int i = 0; i < size; i++)
          {
              if (i != old) 
              {
                  if (matrix[i][old]) matrix[i][in] = true;
                  if (matrix[old][i]) matrix[in][i] = true;
              }
          }
          if (old == size - 1) 
          {
              for (int i = 0; i < size; i++) 
              {
                  matrix[i][old] = false;
              }
              for (int j = 0; j < size; j++) 
              {
                  matrix[old][j] = false;
              }
          }
          else 
          {
              for (int i = old; i < size - 1; i++) 
              {
                  for (int j = 0; j < size; j++)
                  {
                      matrix[i][j] = matrix[i + 1][j];
                  }
              }
              for (int i = 0; i < size; i++) 
              {
                  for (int j = old; j < size - 1; j++) 
                  {
                      matrix[i][j] = matrix[i][j + 1];
                  }
              }
          }
          size--;
     }

    int* matrix_to_arr() 
    {
        int size_of_arr = 0;
        for (int i = 0; i < size; i++) 
        {
            for (int j = 0; j < size; j++) 
            {
                if (matrix[i][j]) size_of_arr++;
            }
        }

        ++size_of_arr *= 2;

        int* arr = new int[size_of_arr];
        int index = 0;
        arr[index++] = size_of_arr;
        arr[index++] = size;
        for (int i = 0; i < size; i++) 
        {
            for (int j = 0; j < size; j++) 
            {
                if (matrix[i][j]) 
                {
                    arr[index++] = i;
                    arr[index++] = j;
                }
            }
        }
        return arr;
    }

    void arr_to_matrix(int* arr)
    {
        clear();
        int n = arr[0];
        for (int i = 2; i < n; i += 2) 
        {
            add_edge(arr[i], arr[i + 1]);
        }
        delete[] arr;
    }

    void writeMatrix() 
    {
        ofstream out;
        out.open("desired_file", ios::binary);
        int* arr = matrix_to_arr();
        int n = arr[0];
        if (out.is_open()) 
        {
            out.write((char*)&(*arr), sizeof(int) * n);
            out.close();
        }
        delete[] arr;
    }

    void readMatrix() 
     {
         ifstream in;
         in.open("desired_file", ios::binary);
         if (in.is_open())
         {
             in.seekg(0, ios::end);
             int n = in.tellg() / 4;
             in.seekg(0, ios::beg);
             int* arr = new int[n];
             in.read((char*)&(*arr), sizeof(int) * n);
             arr_to_matrix(arr);
             in.close();
         }
     }

    void clear() 
     {
         for (int i = 0; i < size; i++) 
         {
             for (int j = 0; j < size; j++)
             {
                 matrix[i][j] = false;
             }
         }
     }

    void print() 
     {
         for (int j = 0; j < size; j++) 
         {
             for (int i = 0; i < size; i++) 
             {
                 cout << matrix[i][j] << "\t";
             }
             cout << endl;
         }
         cout << endl;
     }
};

int main()
{
    newGraph new_created_graph(2);
    new_created_graph.add_edge(0, 3);
    new_created_graph.add_edge(3, 2);
    new_created_graph.add_edge(2, 2);
    new_created_graph.writeMatrix();
    new_created_graph.readMatrix();
    new_created_graph.print();
}