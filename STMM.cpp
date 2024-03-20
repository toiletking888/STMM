#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

struct node {
	string name = "";
	int output[2] = {};
	int nstate[2] = {};
	bool del = false;
};
struct state {
	int in0[2] = {};
	int in1[2] = {};
	bool able = true;
};

void put_node(vector<node> nodes) {
	state array[5][5] = {};
	for (int i = 0; i < 5; i++) {
		for (int j = i; j < 5; j++) {
			if (nodes[i].output[0] == nodes[j + 1].output[0] && nodes[i].output[1] == nodes[j + 1].output[1]) {
				array[i][j].in0[0] = nodes[i].nstate[0];
				array[i][j].in0[1] = nodes[j + 1].nstate[0];
				array[i][j].in1[0] = nodes[i].nstate[1];
				array[i][j].in1[1] = nodes[j + 1].nstate[1];
			}
			else {
				array[i][j].able = false;
				array[i][j].in0[0] = nodes[i].nstate[0];
				array[i][j].in0[1] = nodes[j + 1].nstate[0];
				array[i][j].in1[0] = nodes[i].nstate[1];
				array[i][j].in1[1] = nodes[j + 1].nstate[1];
			}
		}
	}
	gray(array, nodes);
}

void gray(state array[][5], vector<node> nodes) {
	bool exchange = true;
	while (exchange) {
		exchange = false;
		for (int i = 0; i < 5; i++) {
			for (int j = i; j < 5; j++) {
				if (array[i][j].able) {
					int x0 = array[i][j].in0[0];
					int y0 = array[i][j].in0[1];
					int x1 = array[i][j].in1[0];
					int y1 = array[i][j].in1[1];
					if (x0 > y0) {
						int tmp = x0;
						x0 = y0;
						y0 = tmp;
					}
					if (x1 > y1) {
						int tmp = x1;
						x1 = y1;
						y1 = tmp;
					}
					if ((array[x0][y0 - 1].able == false && x0 != y0) || (array[x1][y1 - 1].able == false && x1 != y1)) {
						array[i][j].able = false;
						exchange = true;
					}
				}
			}
		}
	}
	delete_node(array, nodes);
}

void delete_node(state array[][5], vector<node> nodes) {
	for (int i = 0; i < 5; i++) {
		for (int j = i; j < 5; j++) {
			if (array[i][j].able) {
				nodes[j + 1].del = true;
				for (int z = 0; z < 6; z++) {
					if (nodes[z].nstate[0] == j + 1) {
						nodes[z].nstate[0] = i;
					}
					if (nodes[z].nstate[1] == j + 1) {
						nodes[z].nstate[1] = i;
					}
				}
			}
		}
	}
	input_dot(nodes);
}

void input_dot(vector<node> nodes) {
	fstream file;
	file.open("input.dot", ios::out);
	file << "digraph STG {" << endl;
	file << "rankdir=LR;" << endl;
	file << "INIT [shape=point];" << endl;
	for (int i = 0; i < number; i++) {
		file << nodes[i].name << " [label=\"" << nodes[i].name << "\"];" << endl;
	}
	file << "INIT -> " << start << ";" << endl;
	for (int i = 0; i < line; i++) {
		file << nodes[i / 2].name << " -> " << order[nodes[i / 2].nstate[i % 2]] << " [label=\"" << i % 2 << "/" << nodes[i / 2].output[i % 2] << "\"];" << endl;
	}	
	file << "}" << endl;
	file.close();
	put_node(nodes);
}

void the_rest_node(vector<node>nodes) {
	int nod = 0;
	for (int i = 0; i < 6; i++) {
		if (!nodes[i].del) nod++;
	}
	output_kiss(nodes);
}

void output_kiss(vector<node> nodes) {
	fstream fout_kiss;
	fout_kiss.open("output.kiss", ios::out);
	fout_kiss << ".start_kiss" << endl;
	fout_kiss << ".i 1" << endl;
	fout_kiss << ".o 1" << endl;
	fout_kiss << ".p " << nod * 2 << endl;
	fout_kiss << ".s " << nod << endl;
	fout_kiss << ".r " << start << endl;
	for (int i = 0; i < nodes.size() * 2; i++) {
		if (!nodes[i / 2].del) {
			fout_kiss << i % 2 << " ";
			fout_kiss << nodes[i / 2].name << " ";
			fout_kiss << nodes[nodes[i / 2].nstate[i % 2]].name << " ";
			fout_kiss << nodes[i / 2].output[i % 2] << endl;
		}
	}
	fout_kiss << ".end_kiss" << endl;
	output_dot(nodes);
}

void output_dot(vector<node> nodes) {
	fstream fout_dot;
	fout_dot.open("output.dot", ios::out);
	fout_dot << "digraph STG {" << endl;
	fout_dot << "rankdir=LR;" << endl;
	fout_dot << "INIT [shape=point];" << endl;
	for (int i = 0; i < nodes.size(); i++) {
		if (!nodes[i].del) {
			fout_dot << nodes[i].name << " [label=\"" << nodes[i].name << "\"];" << endl;
		}
	}
	fdo << "INIT -> " << start << ";" << endl;
	for (int i = 0; i < nodes.size() * 2; i++) {
		if (!nodes[i / 2].del) {
			fout_dot << nodes[i / 2].name << " -> " << order[nodes[i / 2].nstate[i % 2]] << " [label=\"" << i % 2 << "/" << nodes[i / 2].output[i % 2] << "\"];" << endl;
		}
	}
	fout_dot << "}" << endl;
	fout_dot.close();
}

int main() {
	string order[6] = { "a","b","c","d","e","f" };
	vector<node> nodes;
	string name;
	cin >> name;
	fstream file;
	file.open(name, ios::in);
	string input;
	int line;
	int number;
	string start;
	int s = 0;

	while (file >> input) {
		if (input == ".start_kiss") {

		}
		else if (input == ".i") {
			int a;
			file >> a;
		}
		else if (input == ".o") {
			int a;
			file >> a;
		}
		else if (input == ".p") {
			file >> line;
		}
		else if (input == ".s") {
			file >> number;
			node a;
			for (int i = 0; i < number; i++) {
				nodes.push_back(a);
			}
		}
		else if (input == ".r") {
			file >> start;
		}
		else if (input == ".end_kiss") {
			file.close();
			break;
		}
		else {
			string nows, nexts, out;
			file >> nows >> nexts >> out;
			int x = s / 2;
			int y;
			for (int i = 0; i < 6; i++) {
				if (order[i] == nexts) {
					y = i;
				}
			}
			nodes[x].name = nows;
			nodes[x].nstate[stoi(input)] = y;
			nodes[x].output[stoi(input)] = stoi(out);
			s++;
		}
	}
}