
File3D Start3DTrans(File2D input){
	///Starts the 3D Transformation of the given 2D projections
	///Algorithm for 2D to 3D is inserted here
	File3D outFile;

	vector<PlaneNode3D> Plane_array_out;
	vector<View_Node3D> Node_array_out;
	
	OrthographicView currentView = input.Frontview;

	for(int i=0; i<currentView.node_array.size(); i++){
		View_Node2D nod = currentView.node_array[i];
		
		vector3 coordi(nod.coord.a,nod.coord.b,0,nod.coord.name);
		vector<vector3> arr;
		View_Node3D v(coordi,arr);
		Node_array_out.push_back(v);
	}
	cout <<"Frontview scanned" <<endl;
	currentView = input.Sideview;

	//Coordinate mapping for SideView
	for(int i=0; i<currentView.node_array.size(); i++){
		View_Node2D nod = currentView.node_array[i];
		for (int j = 0; j< Node_array_out.size(); j++){
			if (Node_array_out[j].coord3D.name == nod.coord.name){
				break;
			}
		}

		Node_array_out[j].coord3D.c = (-nod.coord.a);
	}
	cout <<"Sideview scanned" <<endl;
	
	//Now all the nodes have the correct coordinates. We can start to work on Node Array

	for (int i=0; i<Node_array_out.size(); i++){
		View_Node3D temp_vec3D = Node_array_out[i];
		string temp_name = temp_vec3D.coord3D.name;
		//FrontScan
		for (int j= 0; j<input.Frontview.node_array.size(); j++){
			if (input.Frontview.node_array[j].coord.name == temp_name){
				break;
			}
		}
		//For Solid ngb
		for(int k=0; k< input.Frontview.node_array[j].solid_array_neigbour.size(); k++){
			for(int p=0; p< Node_array_out.size(); p++){
				if(Node_array_out[p].coord3D.name == input.Frontview.node_array[j].solid_array_neigbour[k].name){
					break;
				}
			}
			vector3 temp_vec3_ngb = Node_array_out[p].coord3D;
			temp_vec3D.array_neighbour.push_back(temp_vec3);
		}
		//For Dashed ngb
		for(int k=0; k< input.Frontview.node_array[j].dashed_array_neigbour.size(); k++){
			for(int p=0; p< Node_array_out.size(); p++){
				if(Node_array_out[p].coord3D.name == input.Frontview.node_array[j].dashed_array_neigbour[k].name){
					break;
				}
			}
			vector3 temp_vec3_ngb = Node_array_out[p].coord3D;
			temp_vec3D.array_neighbour.push_back(temp_vec3);
		}



		//Top Scan
		for (int j= 0; j<input.Topview.node_array.size(); j++){
			if (input.Topview.node_array[j].coord.name == temp_name){
				break;
			}
		}
		//For Solid ngb
		for(int k=0; k< input.Topview.node_array[j].solid_array_neigbour.size(); k++){

			for (int q =0; q< temp_vec3D.array_neighbour.size(); q++){
				if (temp_vec3D.array_neighbour[q].name ==  input.Topview.node_array[j].solid_array_neigbour[k].name){
					break;
				}
			}

			if (q == temp_vec3D.array_neighbour.size()){
				for(int p=0; p< Node_array_out.size(); p++){
					if(Node_array_out[p].coord3D.name == input.Topview.node_array[j].solid_array_neigbour[k].name){
						break;
					}
				}
				vector3 temp_vec3_ngb = Node_array_out[p].coord3D;
				temp_vec3D.array_neighbour.push_back(temp_vec3);
			}

			
		}
		//For Dashed ngb
		for(int k=0; k< input.Topview.node_array[j].dashed_array_neigbour.size(); k++){

			for (int q =0; q< temp_vec3D.array_neighbour.size(); q++){
				if (temp_vec3D.array_neighbour[q].name ==  input.Topview.node_array[j].dashed_array_neigbour[k].name){
					break;
				}
			}

			if (q == temp_vec3D.array_neighbour.size()){
				for(int p=0; p< Node_array_out.size(); p++){
					if(Node_array_out[p].coord3D.name == input.Topview.node_array[j].dashed_array_neigbour[k].name){
						break;
					}
				}
				vector3 temp_vec3_ngb = Node_array_out[p].coord3D;
				temp_vec3D.array_neighbour.push_back(temp_vec3);
			}
			
		}

		//Side Scan
		for (int j= 0; j<input.Sideview.node_array.size(); j++){
			if (input.Sideview.node_array[j].coord.name == temp_name){
				break;
			}
		}
		//For Solid ngb
		for(int k=0; k< input.Sideview.node_array[j].solid_array_neigbour.size(); k++){

			for (int q =0; q< temp_vec3D.array_neighbour.size(); q++){
				if (temp_vec3D.array_neighbour[q].name ==  input.Sideview.node_array[j].solid_array_neigbour[k].name){
					break;
				}
			}

			if (q == temp_vec3D.array_neighbour.size()){
				for(int p=0; p< Node_array_out.size(); p++){
					if(Node_array_out[p].coord3D.name == input.Sideview.node_array[j].solid_array_neigbour[k].name){
						break;
					}
				}
				vector3 temp_vec3_ngb = Node_array_out[p].coord3D;
				temp_vec3D.array_neighbour.push_back(temp_vec3);
			}

			
		}
		//For Dashed ngb
		for(int k=0; k< input.Sideview.node_array[j].dashed_array_neigbour.size(); k++){

			for (int q =0; q< temp_vec3D.array_neighbour.size(); q++){
				if (temp_vec3D.array_neighbour[q].name ==  input.Sideview.node_array[j].dashed_array_neigbour[k].name){
					break;
				}
			}

			if (q == temp_vec3D.array_neighbour.size()){
				for(int p=0; p< Node_array_out.size(); p++){
					if(Node_array_out[p].coord3D.name == input.Sideview.node_array[j].dashed_array_neigbour[k].name){
						break;
					}
				}
				vector3 temp_vec3_ngb = Node_array_out[p].coord3D;
				temp_vec3D.array_neighbour.push_back(temp_vec3);
			}
			
		}


	}

		//View3DWindow();
	return outFile;
}