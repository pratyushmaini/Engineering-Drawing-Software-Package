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

		for(int j=0; j<nod.solid_array_neighbour.size(); j++){
			vector2 point = nod.solid_array_neighbour[j];
			vector3 coordi1(point.a,point.b,0,point.name);
			arr.push_back(coordi1);	
		}
		for(int j=0; j<nod.dashed_array_neighbour.size(); j++){
			vector2 point = nod.dashed_array_neighbour[j];
			vector3 coordi2(point.a,point.b,0,point.name);		
			arr.push_back(coordi2);	
		}
		View_Node3D v(coordi,arr);
		Node_array_out.push_back(v);
	}
	cout <<"Frontview scanned" <<endl;
	currentView = input.Sideview;

	for(int i=0; i<currentView.node_array.size(); i++){
		View_Node2D nod = currentView.node_array[i];
		
		int l=0;
		for(int j=0; j< Node_array_out.size(); j++){
			if(nod.coord.name==Node_array_out[j].coord3D.name){
				l=j;
				break;
				cout <<"Dashed Scan2" <<endl;
			}
		}
		cout <<"Dashed Scan1" <<endl;
		Node_array_out[l].coord3D.c = (-nod.coord.a);
		cout <<"Dashed Scan5" <<endl;
		if (Node_array_out[l].coord3D.b != nod.coord.b){
			cout<<"ERRROROROROORROROOR" <<endl;
		}

		for(int j=0; j<nod.solid_array_neighbour.size(); j++){
			vector2 point = nod.solid_array_neighbour[j];
			
			vector<vector3> array = Node_array_out[l].array_neighbour;
			cout <<"Dashed Scan6" <<endl;
			int m=-1;
			for(int j=0; ;j++){
				if(point.name==array[j].name){
					m=j;
					break;
					cout <<"Dashed Scan3" <<endl;
				}
			}
			if (m==-1){
				m = j;
				Node_array_out[l].array_neighbour.push_back(point);

			}
			array[m].c=(-point.a);	
		}
		cout <<"Dashed Scan" <<endl;
		for(int j=0; j<nod.dashed_array_neighbour.size(); j++){
			vector2 point = nod.dashed_array_neighbour[j];
			
			vector<vector3> array = Node_array_out[l].array_neighbour;
			
			int m=0;
				for(int j=0; ;j++){
					if(point.name==array[j].name){
						m=j;
						break;
					}
				}
				array[m].c=(-point.a);	
		}
	}
	outFile.Node_array =  Node_array_out;
	outFile.Plane_array  = Plane_array_out;

	cout<< "Output Ready" <<endl;
	//View3DWindow();
	return outFile;
}
