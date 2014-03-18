JsonCppWrapper
==============

A wrapper to provide a simpler interface to the libjsoncpp. It makes it easier to add new objects, get objects' contents, add arrays and add object to arrays. It's a pretty easy and straight-forward to use wrapper.

Example Usage
================
int main()
{
    FUJsonCppWrapper handler;
    //Load the json file first. Calling this unloads the previous file and loads the new one
    handler.loadJsonFile("/home/furkan/Json.json");
    //Create a vector and add some items
    std::vector<std::string> vector;
    vector.push_back("One");
    vector.push_back("Two");
    //Add a new array
    handler.addNewArray("Array", vector);
    //You can add objects to array
    handler.addObjectToArray("Array", "Name", "Furkan");
    std::vector<Json::Value> val = handler.getArray("Array");
    for (Json::Value &value : val)
        std::cout << value << std::endl;
    std::cout << handler.getObjectInValue("Name", &handler.getArray("Array").at(2)) << std::endl;
    return 0;
}

Dependincies
=================
Obviously you need JsonCpp --> http://jsoncpp.sourceforge.net/
You can install the library through your Linux distro's package manager.
If you're using Windows, just compile the code and add the library to the project you're using. Don't forget to set the appropriate include paths.