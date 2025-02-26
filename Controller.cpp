#include "Controller.h"
#include "sgraph/IScenegraph.h"
#include "sgraph/Scenegraph.h"
#include "sgraph/GroupNode.h"
#include "sgraph/LeafNode.h"
#include "sgraph/ScaleTransform.h"
#include "ObjImporter.h"
using namespace sgraph;
#include <iostream>
using namespace std;

#include "sgraph/ScenegraphExporter.h"
#include "sgraph/ScenegraphImporter.h"

Controller::Controller(Model& m, View& v, const std::string& filePath) {
    model = m;
    view = v;

    initScenegraph(filePath);
}

void Controller::initScenegraph(const std::string& filePath) {
    ifstream inFile(filePath);
    if (!inFile) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        exit(EXIT_FAILURE);
    }
     
    
    //read in the file of commands
    //ifstream inFile("scenegraphmodels/face-hierarchy-commands.txt");
    //ifstream inFile("tryout.txt");
    sgraph::ScenegraphImporter importer;
    

    IScenegraph *scenegraph = importer.parse(inFile);
    //scenegraph->setMeshes(meshes);
    model.setScenegraph(scenegraph);
    cout <<"Scenegraph made" << endl;   

}

Controller::~Controller()
{
    
}

void Controller::run()
{
    sgraph::IScenegraph * scenegraph = model.getScenegraph();
    map<string,util::PolygonMesh<VertexAttrib> > meshes = scenegraph->getMeshes();
    view.init(this,meshes);
    while (!view.shouldWindowClose()) {
        view.display(scenegraph);
    }
    view.closeWindow();
    exit(EXIT_SUCCESS);
}

void Controller::onkey(int key, int scancode, int action, int mods)
{
    cout << (char)key << " pressed" << endl;
}

void Controller::reshape(int width, int height) 
{
    cout <<"Window reshaped to width=" << width << " and height=" << height << endl;
    glViewport(0, 0, width, height);
}

void Controller::dispose()
{
    view.closeWindow();
}

void Controller::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}