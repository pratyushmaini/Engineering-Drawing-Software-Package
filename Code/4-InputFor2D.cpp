#include <gtk/gtk.h>
#include <string.h>
#include <GL/glui.h>
#include <fstream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include "File2D_3D.h"
using namespace std;


string inputDirectory;
File2D* fileLabelled;
bool done=false;
int mode2Dfile = 2;
extern File2D printFile;
extern void home();

static void open_dialog(GtkWidget* button, gpointer window)
{
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Choose file", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_widget_show_all(dialog);
//  gtk_file_chooser_set_curr_fileent_folder(GTK_FILE_CHOOSER(dialog),"/");
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), g_get_home_dir());
    gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
    if(resp == GTK_RESPONSE_OK){
        g_print("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
        inputDirectory = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        done = true;
    }
    else
        g_print("You pressed Cancel\n");
    gtk_widget_destroy(dialog);
}

int main2Dinput(int argc, char* argv[])
{
    gtk_init(&argc, &argv);
    GtkWidget *window, *button;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    button = gtk_button_new_with_label("Open File");
    g_signal_connect(button, "clicked", G_CALLBACK(open_dialog), window);
    gtk_container_set_border_width(GTK_CONTAINER(window), 100);
    gtk_container_add(GTK_CONTAINER(window), button);


    gtk_widget_show_all(window);

	gtk_main();

    if(done == true){
    	cout<< "here" << endl;
    	//gtk_widget_destroy(window);
    }

    return 0;
}
///Labeled File
///Unlabeled File 
///Get users to label it.
GLUI *glui_2dinput;

extern int main_window;
// extern int window_num;
#define Label2D             400
#define Unlabel2D           401
#define TransformFileto3D   402
#define Back4 				403


void file_2d_printer(){
	
}

void control_cb_2D_file( int control )
{  

  if ( control == Label2D )
  {
  	mode2Dfile = 0;
  }
  else if ( control == Unlabel2D )
  {
    mode2Dfile = 1;
  }
  else if ( control == TransformFileto3D )
  {
    
    glui_2dinput -> close();
    
  }
  else if ( control == Back4 ){
    glui_2dinput -> close();
    window_num = 1;
    home();
  }

}



File2D Takeinput(){
	///Browse from directory
	cout<<3473298732947<<endl;
  	int zero =main2Dinput(NULL, NULL);

  	cout << 12435366 <<endl;
  	
  	ifstream inFile;

  	cout << 123;
  	inFile.open(inputDirectory);
  	if (!inFile) {
    	cout << "Unable to open file datafile.txt";
    	exit(1);   // call system to stop
	}

	int n, ins_view=0;
	float a,b;
	string str,s;

	// cout<<786;
	fileLabelled = new File2D;

	while (getline(inFile, str)) {

	  //vector<View_Node2D> n_arr;

	  inFile >> n;
	  for(int i=0; i<n; i++){
		inFile >> a;
		inFile >> b;
		inFile >> s;
		vector2 coord1(a,b,s);
		vector<vector2> solid, dash;	

		int no_of_nebor;
		inFile >> no_of_nebor;
		for(int j=0; j<no_of_nebor; j++){
			inFile >> a;
			inFile >> b;
			inFile >> s;
			cout << s;
			vector2 coord2(a,b,s);
			solid.push_back(coord2);
		}
		inFile >> no_of_nebor;
		for(int j=0; j<no_of_nebor; j++){
			inFile >> a;
			inFile >> b;
			inFile >> s;
			vector2 coord2(a,b,s);
			dash.push_back(coord2);
		}
		View_Node2D node(coord1, solid, dash);
		// n_arr.push_back(node);
		if(ins_view==0){
			fileLabelled ->Frontview.node_array.push_back(node);
		}
		else if(ins_view==1){
			fileLabelled ->Sideview.node_array.push_back(node);
		}
		else{
			fileLabelled ->Topview.node_array.push_back(node);			
		}
	  }
	  getline(inFile, str);
	  cout<< 1;
	  ins_view++;
	}


  	// cout<<"done";

	inFile.close();
	// cout<< 4354543;
	// cout<< sum << endl;

  	cout<<"done";
	File2D file = *fileLabelled;
	//insert code
	
	return file;
}

void File2D::getLabels(){
	///Convert into labeled file by taking input
}

File2D File2DInput(){
	///Manages the further action depending on mode selected
		// cout<<4817894173<<endl;

	glui_2dinput = GLUI_Master.create_glui_subwindow( main_window, 
              			GLUI_SUBWINDOW_RIGHT );

	/*** Disable/Enable buttons ***/
 	new GLUI_Button( glui_2dinput, "Labeled Input", Label2D, control_cb_2D_file );
  	new GLUI_Button( glui_2dinput, "Unlabeled Input", Unlabel2D, control_cb_2D_file );
  	new GLUI_Button( glui_2dinput, "3D Transformation", TransformFileto3D, control_cb_2D_file);
  	new GLUI_Button( glui_2dinput, "Back", Back4, control_cb_2D_file);
  	
	// int mode = chooseMode();
			// cout<<4817894173<<endl;

	File2D input;

			cout<<"hehe"<<endl;


	if(mode2Dfile == 0){
		input = Takeinput();
	}
	else {
		input = Takeinput();
		input.getLabels();		
	}

	glui_2dinput->close();
	window_num = 3;
	cout << 943289408329 << endl;
	printFile = input;
	input = Line2DInput(input);
	return input;
}