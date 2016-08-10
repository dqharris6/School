#include "Project_Window.h"
using namespace Graph_lib;

// Call new window class Project_Window, define buttons, boxes, and other widgets
Project_Window::Project_Window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
    back_button(Point(40,210), 150, 40, "<< Back", cb_back),
    next_button(Point(610,210), 150, 40, "Next >>", cb_next),
    attach_button(Point(500,450), 100, 20, "Store Name", cb_attach),
    attach_tags_button(Point(500,480), 100, 20, "Store Tags", cb_attach_tags),
    attach_all_images_button(Point(500,420), 100, 20, "Attach Images",
    	cb_attach_all_images),
    tags_name(Point(275,480), 220, 20, "Tags (Separated by Spaces): "),
    file_name(Point(275,450), 220, 20, "File Name: "),
    tags_output(Point(275,420), 220, 20, "Current Tags: "), 
    picture_window(Point(200,30),400,380, ""),
    button_pushed(false)
{
// Attach each of the widgets defined above to the window
    attach(back_button);
    attach(next_button);
	attach(attach_button);
	// attach(attach_tags_button);
	attach(attach_all_images_button);
    attach(tags_name);
    attach(file_name);
    attach(tags_output);
    attach(picture_window);
}

// Declare and define some local variables: iostreams, vectors, ints, strings
	ifstream index_input("index.txt");
	ofstream index_output("index.txt", std::ofstream::app);
	istringstream index_input_stringstream;
			
    Vector_ref<Image> images;
    Vector_ref<string> tag_strings;
    Vector_ref<string> search_tags;
    
    int images_pointer = 0;
    string file, tags, tags_concatenated, title_name, images_pointer_string, tag;

bool Project_Window::wait_for_button()
{
    show();
    button_pushed = false;
#if 1
    while (!button_pushed) Fl::wait();
    Fl::redraw();
#else
    Fl::run();
#endif
    return button_pushed;
}

// Define callback functions for the BACK button
void Project_Window::cb_back(Address, Address pw)
{  
    reference_to<Project_Window>(pw).back_button_function();    
}

void Project_Window::back_button_function()
{
	if(images_pointer == 0) {redraw();}
	else
	{
		tags_output.put(" ");
		images_pointer_string = std::to_string(images_pointer-1);
		detach(images[images_pointer]);
		--images_pointer;
		attach(images[images_pointer]);
		// tags_output.put(tag_strings[images_pointer]);
		tags_output.put(images_pointer_string);
		redraw();
	}
}

// Define callback functions for the NEXT button
void Project_Window::cb_next(Address, Address pw)
{  
    reference_to<Project_Window>(pw).next_button_function();    
}

void Project_Window::next_button_function()
{
	if(images_pointer == images.size()-1) {redraw();}
	else
	{
		tags_output.put(" ");
		images_pointer_string = std::to_string(images_pointer+1);
		detach(images[images_pointer]);
		++images_pointer;
		attach(images[images_pointer]);
		// tags_output.put(tag_strings[images_pointer]);
		tags_output.put(images_pointer_string);
		redraw();
	}
}

// Define callback functions for the ATTACH NEW button
void Project_Window::cb_attach(Address, Address pw)
{  
    reference_to<Project_Window>(pw).attach_to_window();    
}

void Project_Window::attach_to_window()
{
    file = file_name.get_string();
	images.push_back(new Image(Point(210,40), file));
    index_output << file << " ";
    tags = tags_name.get_string();
    tags_output.put(tags);
    index_output << tags << endl;
    attach(images[images.size()-1]);
    redraw();
}

// Define callback functions for the TAGS button (no longer used)
void Project_Window::cb_attach_tags(Address, Address pw)
{  
    reference_to<Project_Window>(pw).attach_tags_to_window();    
}

void Project_Window::attach_tags_to_window()
{
    tags = tags_name.get_string();
    index_output << tags << endl;
    redraw();
}

// Define callback functions for the ATTACH ALL button
void Project_Window::cb_attach_all_images(Address, Address pw)
{  
    reference_to<Project_Window>(pw).attach_all_images();    
}

void Project_Window::attach_all_images()
{
	istringstream index_input_stringstream;
	while(!index_input.eof())
    {
    	index_input >> title_name;
    	getline(index_input,tags_concatenated);
		cout << tags_concatenated << endl;
		tag_strings.push_back(tags_concatenated);
    	tags_output.put(tags_concatenated);
		images.push_back(new Image(Point(210,40), title_name));
		images_pointer++;
		tags_concatenated = " ";	
    }
    attach(images[images.size()-1]);
    images_pointer--;
    
    for(int loop = 0; loop < tag_strings.size(); ++loop) // checks to see what is in vector
		cout << tag_strings[loop] << endl;
    
    redraw();
}