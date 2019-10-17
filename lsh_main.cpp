#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <unordered_map>
#include <limits>

using namespace std;

#include "query_result/query_result.hpp"
#include "item/item.hpp"
#include "lsh/lsh.hpp"
#include "hash_table/hash_table.hpp"
#include "helping_functions/helping_functions.hpp"

#define L_DEFAULT 5
#define K_DEFAULT 4
#define W_DEFAULT 100
#define SEARCH_THRESHOLD (L_DEFAULT*10)

int main(int argc, char *argv[]) {
	int L = L_DEFAULT;
	int k = K_DEFAULT;
	int w = W_DEFAULT;
	int search_threshold = SEARCH_THRESHOLD;

	if (argc < 3 ) {
		cout <<"usage: ./lsh –d <input file> –q <query file> –k <int> -L <int> -ο <output file>"<<endl;
		return 1;
	}
	
	//READ COMMAND LINE ARGUMENTS
	string input_file, query_file, output_file;
	read_command_line_arguments(argv, argc, input_file, query_file, output_file,
			k, L, w, search_threshold);

	//READ ITEMS FROM THE INPUT FILE
	list<Item*> input_items;
	read_vectors_from_file(input_file, input_items);
	int dimension = input_items.front()->get_coordinates()->size();
	unsigned m = numeric_limits<unsigned>::max() - 5;
	print_parameters(L, k, w, search_threshold, dimension);

	//CREATE THE LSH STRUCTURE
	LSH lsh(L, dimension, w, k, m);

	
	//INSERT INPUT DATA
	time_t time = clock();
	for(Item *item: input_items) {
		lsh.insert_item(item);
	}
	time = clock() - time;
	cout <<"Data insertion total time: "<< ((double)time) / CLOCKS_PER_SEC <<endl<<endl;


	//HANDLE QUERIES
	list<Item*> queries;
	read_vectors_from_file(query_file, queries);

	Query_Result ann_query_result, exhaustive_query_result;
	time = clock();
	double sum_query_time = 0;
	double max_rate = -1;
	double sum_rate = 0;
	int found_nearest = 0;
	int total_distances = 0;
	int not_null = 0;
	for(Item *query: queries) {
		//cout <<"Query:"<<query->get_name()<<endl;

		//approximate nearest neighbor
		lsh.ANN(query, search_threshold, ann_query_result);
		//print_ann_results(ann_query_result);

		//Exact nearest neighbor
		exhaustive_search(&input_items, query, exhaustive_query_result);
		//print_exhaustive_search_results(exhaustive_query_result);
		//cout<<endl;

		//statistics info
		if (ann_query_result.get_time() != -1) {
			sum_query_time += ann_query_result.get_time();
			max_rate = max(max_rate, (double)ann_query_result.get_best_distance()/exhaustive_query_result.get_best_distance());
			sum_rate += ann_query_result.get_best_distance()/exhaustive_query_result.get_best_distance();
			if (ann_query_result.get_name() == exhaustive_query_result.get_name()) {
				found_nearest++;
			}
			total_distances += ann_query_result.get_best_distance();
			not_null++;
		}

	}
	time = clock() - time;
	cout <<"Handling of queries(ann and enn) total time: "<< ((double)time) / CLOCKS_PER_SEC<<endl;
	cout << "Average query time: "<<sum_query_time/not_null<<endl;
	cout << "Max rate: "<<max_rate<<endl;
	cout << "Average rate: "<<sum_rate/not_null<<endl;
	cout << "Found "<<not_null<<"/"<<queries.size()<<" approximate nearest neighbors"<<endl;
	cout << "Found "<<found_nearest<<"/"<<queries.size()<<" exact nearest neighbors"<<endl;
	cout << "Average distance: "<<total_distances/queries.size()<<endl;
	cout <<"--------------------------------------------------------------------------"<<endl;
	cout <<endl;
	
	delete_items(input_items);
	delete_items(queries);
	return 0;
}