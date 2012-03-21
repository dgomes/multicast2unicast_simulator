
#include "Parser.h"

#include "kml/dom.h"
//#include "kml/dom/xsd.h"
#include "kml/engine.h"
#include "kml/base/file.h"
#include <fstream>

using kmlengine::KmzFile;
using kmldom::CoordinatesPtr;
using kmldom::KmlPtr;
using kmldom::KmlFactory;
using kmldom::PlacemarkPtr;
using kmldom::PointPtr;
using kmldom::FolderPtr;


// This ParserObserver uses the NewElement() method to count the number of
// ocurrences of each type of element.
class MyParserObserver : public kmldom::ParserObserver {
 public:
  // ParserObserver::NewElement()
  virtual bool AddChild(const kmldom::ElementPtr& element, const kmldom::ElementPtr& child) {
    if (element->Type() == kmldom::Type_Placemark && child->Type() == kmldom::Type_Point) {
		kmldom::PlacemarkPtr placemark = AsPlacemark(element);
		if (placemark->has_geometry()) {
			if (const kmldom::PointPtr point = kmldom::AsPoint(placemark->get_geometry() )) { 
    			// Yes, it is a Point... see if it has coordinates:
    			if (point->has_coordinates()) {
					kmldom::CoordinatesPtr c = point->get_coordinates();

					parsed.push_back(Coordinate(point->get_coordinates()->get_coordinates_array_at(0).get_latitude(),
                        point->get_coordinates()->get_coordinates_array_at(0).get_longitude()));

					//P_DEBUG("Push back");
    			}
  			}
		}

	}
    return true;  // Always return true to keep parsing.
  }
  std::list<Coordinate> parsed;
};

std::list<Coordinate> KML_parser::parse() { 
	// Read the file.
  	std::string file_data;
  	if (!kmlbase::File::ReadFileToString(filename, &file_data)) {
   		cerr << filename << " read failed" << endl;
  		//throw std::logic_error("Failed to read file");
		return std::list<Coordinate>();
	}

 	// Parse it with the ElementCounter installed as a ParseObserver.
	kmldom::Parser parser;
	MyParserObserver observer;
	parser.AddObserver(&observer);
	std::string errors;
	kmldom::ElementPtr root = parser.Parse(file_data, &errors);
	if (!root) {
		cout << errors << endl;
  		throw std::logic_error(errors);
 	}
	P_DEBUG_MAX("Parsing done!");
	return observer.parsed;
};

void KML_parser::save(std::list<Coordinate> &c, std::string name) {
	P_DEBUG_MAX("KML_parser::save() " << c.size() << " " << name);
 
	// Get the factory singleton to create KML elements.
	KmlFactory* factory = KmlFactory::GetFactory();
  	// Create <kml> and give it <Placemark>.
	KmlPtr kml = factory->CreateKml();
  	FolderPtr folder = factory->CreateFolder();
	folder->set_name(name);

	std::list<Coordinate>::iterator i;
	unsigned p = 0;
	for(i = c.begin(); i != c.end(); ++i) {
		p++;
  		// Create <coordinates>.
		CoordinatesPtr coordinates = factory->CreateCoordinates();
		coordinates->add_latlng(i->getLatitude(), i->getLongitude());

  		// Create <Point> and give it <coordinates>.
  		PointPtr point = factory->CreatePoint();
  		point->set_coordinates(coordinates);  // point takes ownership

  		// Create <Placemark> and give it a <name> and the <Point>.
  		PlacemarkPtr placemark = factory->CreatePlacemark();
  		placemark->set_name(to_string(p) +" - "+ name);
  		placemark->set_geometry(point);  // placemark takes ownership
		
		folder->add_feature(placemark);
	}

  	kml->set_feature(folder);  // kml takes ownership.
  	// Serialize to XML
  	std::string xml = kmldom::SerializePretty(kml);

  	std::ofstream kml_save_file(filename.c_str());
  	if(kml_save_file.is_open()) {
    	kml_save_file << xml;
		kml_save_file.close();
  	}
	else cerr << "Unable to open file "<< filename << endl;

}
