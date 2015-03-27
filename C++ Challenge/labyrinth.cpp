#include <fstream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

void DFS(vector< vector<string> > &maze, vector< vector<bool> > &visited, int &max_len, vector< pair<int,int> > &max_path, vector< pair<int,int> > &path)
{
	int x = path.back().first, y = path.back().second, x_max = maze.size()-1, y_max = maze[0].size()-1;
	visited[x][y] = 1;
	if(x>0)
		if(maze[x-1][y]=="." && !visited[x-1][y])
		{
			path.push_back(make_pair(x-1,y));
			DFS(maze, visited, max_len, max_path, path);
		}
	if(y<y_max)
		if(maze[x][y+1]=="." && !visited[x][y+1])
		{
			path.push_back(make_pair(x,y+1));
			DFS(maze, visited, max_len, max_path, path);
		}
	if(x<x_max)
		if(maze[x+1][y]=="." && !visited[x+1][y])
		{
			path.push_back(make_pair(x+1,y));
			DFS(maze, visited, max_len, max_path, path);
		}
	if(y>0)
		if(maze[x][y-1]=="." && !visited[x][y-1])
		{
			path.push_back(make_pair(x,y-1));
			DFS(maze, visited, max_len, max_path, path);
		}
	if(path.size() > max_len)
	{
		max_len = path.size();
		max_path.resize(max_len);
		for(int i=0; i<path.size(); i++)
			max_path[i] = path[i];
	}
	path.pop_back();
	return;
}

int main()
{
	vector< vector<string> > maze;
	vector< vector<bool> > visited;
	// Get the maze from input file.
	ifstream infile;
	infile.open("input.txt");
	if(!infile.is_open())
		return 0;
	while(!infile.eof())
	{
		string data;
		infile>>data;
		vector<string> split_data;
		vector<bool> visited_row;
		for(int i=0; i<data.size(); i++)
		{
			string s;
			visited_row.push_back(0);
			s.push_back(data[i]);
			split_data.push_back(s);
		}
		maze.push_back(split_data);
		visited.push_back(visited_row);
	}
	infile.close();
	int maze_x_max = maze.size()-1, maze_y_max = maze[0].size()-1;

	// Search for the longest path.
	int max_len = 0;
	vector< pair<int,int> > max_path;
	for(int i=0; i<=maze_x_max; i++)
		for(int j=0; j<=maze_y_max; j++)
		{
			if(maze[i][j] == ".")
			{
				int len = 1;
				vector< pair<int,int> > path, temp_path;
				path.push_back(make_pair(i,j));
				temp_path.push_back(make_pair(i,j));
				DFS(maze, visited, len, path, temp_path);
				if (len > max_len)
				{
					max_len = len;
					max_path.resize(max_len);
					for(int i=0; i<path.size(); i++)
						max_path[i] = path[i];
				}
				for(int i=0; i<=maze_x_max; i++)
					for(int j=0; j<=maze_y_max; j++)
						visited[i][j] = 0;
			}
		}

	// Update maze by specifying longest path.
	for(int i=0; i<max_len; i++)
		maze[max_path[i].first][max_path[i].second] = to_string(i);

	// Put the result to output file.
	ofstream outfile;
	outfile.open("output.txt");
	for(int i=0; i <= maze_x_max; i++)
	{
		string s;
		for(int j=0; j <= maze_y_max; j++)
			s.append(maze[i][j]);
		outfile<<s<<endl;
	}
	outfile.close();
	return 0;
}