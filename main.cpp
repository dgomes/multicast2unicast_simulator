#include <iostream>
#include "config.h"
#include "Terminal.h"
#include "WifiCell.h"
#include "UMTSCell.h"
#include "World.h"
#include "Parser.h"
#include "configuration.h"

#include "utils.h"
using std::cout;
using std::endl;

int run (int argc, char * const argv[]) {
	configuration conf("config.cfg");

	/* Load services */
	std::vector<std::pair<Service,double> > service_channel; //Service,Share 
	std::map<std::string,unsigned> abs_share;
	for(unsigned i=1; i<=conf["service"].size(); i++) { 
		Service s(conf["service"][to_string(i)]["bw"].value(0),multicast,conf["service"][to_string(i)].value("service"));
		service_channel.push_back(std::make_pair(s,conf["service"][to_string(i)]["share"].value(0)/100.0));
		abs_share[conf["service"][to_string(i)].value("service")] = 0;	
	}

	/* create campus */
	Coordinate sw(conf["sw"]["lat"].value(40.632980),conf["sw"]["lon"].value(-8.660979));
	Coordinate ne(conf["ne"]["lat"].value(40.634977),conf["ne"]["lon"].value(-8.657992));
	World campus(sw,ne);

	/* Load Cells */
	KML_storage<UMTSCell> cells("cells.kml");
	if(!(argc>1 && !strcmp(argv[1],"save")))
		cells.dontSave();
	if(!cells.size()) {
		cerr << "Generating new cells" << endl;
		std::vector<Coordinate> newcells = campus.generatePerfectUniformDistribution(conf["cell"]["distance"].value(0.025));
		P_DEBUG("Generated " << newcells.size() << " cells");
		for(unsigned i=0; i < newcells.size(); i++) {
			UMTSCell w(newcells[i]);
			cells.store(w);
		}
	} else {
		cerr << "Read " << cells.size() << " cells from cells.kml" << endl;
	}
	campus.placeCells<UMTSCell>(cells.getElements());

	/* Load terminals */
	KML_storage<Terminal> terminals("terms.kml");
	if(!(argc>1 && !strcmp(argv[1],"save")))
		terminals.dontSave();
	if(!terminals.size()) {
		cerr << "Generating new terminals" << endl;
		std::vector<Coordinate> newterms = campus.generateNormalDistribution(conf["terminals"]["amount"].value(20), campus.getMiddle(), 0.0250);
		for(unsigned i=0; i < newterms.size(); i++) {
			Terminal t(newterms[i]);
			terminals.store(t);
		}
	}
	campus.placeTerminals<Terminal>(terminals.getElements());

	/* assign terminals to cells */
	double coverage_rate = campus.calculateCoverage()*100.0/terminals.size();

	/* Distribute Services through the terminals */
	boost::rand48 engine;
	engine.seed((int)time(0));
	boost::uniform_int<int> percentage(0,terminals.size());
    boost::variate_generator<boost::rand48&, boost::uniform_int<int> > generator(engine, percentage);

	for(std::list<Terminal>::iterator term = terminals.getElements().begin(); term!=terminals.getElements().end(); ++term) {
		unsigned rifa = generator();
		double share=0.0;
		for(unsigned i=0; i<service_channel.size(); i++) {
			share+=service_channel[i].second;
			if(rifa <= share*terminals.size()) {
				term->subscribeService(service_channel[i].first);
				term->startService();
				abs_share[service_channel[i].first.getName()]+=1;
				break;
			}
		}
	}
	// Validate Error rate
	unsigned s = 1;
	for(std::map<std::string, unsigned>::iterator i = abs_share.begin(); i != abs_share.end(); ++i, s++) { 
		double predicted = conf["service"][to_string(s)]["share"].value(0)/100.0;
		double got = ((double)i->second/terminals.size());
		double erro = fabs(predicted-got);
		if(erro > conf["general"]["service"]["error"].value(0.10)*predicted) {
			cerr << "Service " << conf["service"][to_string(s)].value("service") << " (" << predicted << ") distribution has " << got << " with an error (" << erro << ") greater then " << conf["general"]["service"]["error"].value(0.10)*predicted << "%" << endl;
			cerr << "ABORTING SIMULATION" << endl;
			return EXIT_FAILURE;
		}
	}

	/* print statistics */	
	unsigned t;
	cerr << "World: " << endl << campus << endl;
	cout << "Coverage Rate: " << coverage_rate << "%"<< endl;

	t = 1;
	for(std::map<std::string, unsigned>::iterator i = abs_share.begin(); i != abs_share.end(); ++i, t++) { 
		double predicted = conf["service"][to_string(t)]["share"].value(0)/100.0;
		double got = ((double)i->second/terminals.size());
		double erro = fabs(predicted-got);
		cout << i->first << ", " << 100*got <<"%"<<  " +-" << 100*erro << "%"<< endl;
	}

	t = 1;
	cout << "Cell Name, Number of Stations Associated, Number of Statition served with Multicast Services, Number of Multicast Services";
	for(std::vector<std::pair<Service,double> >::iterator service = service_channel.begin(); service != service_channel.end(); service++, t++)
		cout << ", Service " << t;
	cout << endl; 
	t=1;
	for(std::list<UMTSCell>::iterator i = cells.getElements().begin(); i!= cells.getElements().end(); ++i,t++) {	
		if(i->getNumberOfClients()) {
			cout << t << " - " << typeid(*i).name() << "," << i->getNumberOfClients() << "," << i->getNumberOfMulticastSubscribers() << "," << i->getNumberOfMulticastServices();
			for(std::vector<std::pair<Service,double> >::iterator service = service_channel.begin(); service != service_channel.end(); service++)
				cout << "," << i->getNumberOfMulticastSubscribersPerService(&(service->first));
			cout << endl;
		}
	}
	return EXIT_SUCCESS;
}

int main (int argc, char * const argv[]) {
	cout << "Multicast to Unicast Simulator\n";

	do {
		if(!run(argc,argv)) break;
	} while(true);	
}

