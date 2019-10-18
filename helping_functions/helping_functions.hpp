#ifndef HELP_H
#define HELP_H

#include <list>
#include "../query_result/query_result.hpp"
#include "../curve/curve.hpp"
#include "../point/point.hpp"

unsigned mod(long long a, long long b);
unsigned add_mod(long long a, long long b, long long m);
uint32_t mul_mod(long long a, long long b, long long m);
uint32_t mul_mod2(uint32_t a, uint32_t b, uint32_t m) ;
uint32_t pow_mod(uint32_t a, uint32_t b, uint32_t m);
void random_float_list(double from, double to, list<float>& random_list, int size);
void random_float_vector(double from, double to, vector<float>& random_vector, int size);
int max_from_list(list<int> my_list);
int max_from_list(list<float> my_list);
int max_from_vector(vector<float> my_vector);
int max_from_vector(vector<int> my_vector);
int find_dimension_from_file(string file_name);
void print_vector(vector<int> my_list);
void print_vector(vector<float> my_list);
unsigned g_hash_function(vector<Type> x , int dimension, int w, int k,
		int bits_of_each_hash, unsigned M, vector<vector<float>*>& s_array, vector<unsigned>& m_powers);
unsigned hash_function(vector<Type> x, int dimension, int w, unsigned M,
		vector<float>& s, vector<unsigned>& m_powers);
void read_command_line_arguments(char *argv[], int& argc, string& input_file, string& query_file,
	string& output_file, int& k, int& L, int& w, int& st);
void read_command_line_arguments(char *argv[], int& argc, string& input_file, string& query_file,
	string& output_file, int& k, int& L, int& w, int& st, bool& check_for_identical_grid_flag, int& delta);
unsigned long long int manhattan_distance(vector<Type> x1, vector<Type> x2);
void print_ann_results(Query_Result ann_result);
void print_exhaustive_search_results(Query_Result exhaustive_result);
void print_parameters(int L, int k, int w, int search_threshold, int dimension);
void print_parameters(int L, int k, int w, int search_threshold, int dimension, int delta);
void get_vector_from_line(string line, Item& item);
void read_vectors_from_file(string file_name, list<Item*>& items);
unsigned long long int manhattan_distance(vector<Type> x1, vector<Type> x2);
void exhaustive_search(list<Item*> *items, Item *query, Query_Result& query_result);
void delete_items(list<Item*> items);

int read_2d_curves_from_file(string file_name, list<Curve*>& curves, int& max_length);
void print_curves(list<Curve*> curves);
void delete_curves(list<Curve*> curves);
void exhaustive_curve_search(list<Curve*> *curves, Curve *query, Query_Result& query_result);

Type DTW(vector<Point*> p, vector<Point*> q);
float manhattan_distance_2d(Point *p, Point *q);

/*
// count coordinates on "file_name"'s first line(except vector's name)
int find_dimension_from_file(string file_name);

// count lines of the "file_name"
int get_lines_of_file(string file_name);

int print_input_file(string file_name);

//fill "random_array" of size "size" with uniformly distributed doubles in range ["from", to)
void random_double_array(double from, double to, double *random_array, int size); //[from, to)

//fill "random_array" of size "size" with uniformly distributed floats in range ["from", to)
void random_float_array(double from, double to, float *random_array, int size); //[from, to)

//fill "random_list" with "size" uniformly distributed floats/ints in range ["from", "to")
void random_int_list(double from, double to, list<int>& random_list, int size);

//get a uniformly distributed double in range ["from", to)
double random_double(double from, double to);

//get a uniformly distributed float/int in range ["from", to]
float random_float(double from, double to);
int random_int(int from, int to);

void print_array(double array[], int size);
void print_array(float array[], int size);
void print_array(int array[], int size);

int max_from_array(int array[], int size);
float max_from_array(float array[], int size);
double max_from_array(double array[], int size);

// a*b mod m
uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t m); 

// a^b mod m
uint64_t pow_mod(uint64_t a, uint64_t b, uint64_t m);

*/

#endif