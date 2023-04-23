/* \author Aaron Brown */
// Quiz on implementing kd tree

#include "../../render/render.h"


// Structure to represent node of kd tree
struct Node
{
	std::vector<float> point;
	int id;
	Node* left;
	Node* right;

	Node(std::vector<float> arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL)
	{}
};

struct KdTree
{
	Node* root;

	KdTree()
	: root(NULL)
	{}

	void insert(std::vector<float> point, int id)
	{
		// TODO: Fill in this function to insert a new point into the tree
		// the function should create a new node and place correctly with in the root 
		auto cur = root;
		insertHelper(root, point, id, 0);


	}

	void insertHelper(Node*& cur, std::vector<float> point, int id, int depth) {
		if (cur == nullptr) {
			cur = new Node(point, id);
			std::cout<<"insert:"<<point[0]<<" "<<point[1]<<"at depth"<<depth<<std::endl;
			return;
		} 
		if (depth % 2 == 0) { //check x
			if (cur->point[0] > point[0]) {
				insertHelper(cur->left, point, id, depth + 1);
			} else {
				insertHelper(cur->right, point, id, depth + 1);
			}
		} else {
			if (cur->point[1] > point[1]) {
				insertHelper(cur->left, point, id, depth + 1);
			} else {
				insertHelper(cur->right, point, id, depth + 1);
			}
		}
	}

	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(std::vector<float> target, float distanceTol)
	{
		std::vector<int> ids;
		searchHelper(root, target, distanceTol, 0, ids);
		return ids;
	}
	void searchHelper(Node* cur, std::vector<float> target, float distanceTol, int depth, std::vector<int>& ids) {
		int idx = depth % 2;
		if (cur != nullptr) {
			if ( (cur->point[0] >= (target[0] - distanceTol) && cur->point[0] <= (target[0] + distanceTol))
			 && (cur->point[1] >= (target[1] - distanceTol) && cur->point[1] <= (target[1] + distanceTol)) ) {
				 float distance = sqrt((cur->point[0] - target[0]) * (cur->point[0] - target[0]) +
				 					   (cur->point[1] - target[1]) * (cur->point[1] - target[1]));
				 if (distance <= distanceTol) {
					 ids.push_back(cur->id);
				 }
			}
			if ((target[idx] - distanceTol) < cur->point[idx]) {
				searchHelper(cur->left, target, distanceTol, depth + 1, ids);
			}
			if ((target[idx] + distanceTol) > cur->point[idx]) {
				searchHelper(cur->right, target, distanceTol, depth + 1, ids);
			}
		}
		
	}
	

};




