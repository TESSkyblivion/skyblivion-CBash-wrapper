#include <sstream>
#include <iostream>
#include <boost/regex.hpp>
#include "CBash/src/Skyblivion/Skyblivion.h"

using namespace Skyblivion;

void convertACTI(SkyblivionConverter &converter) {
	TES4File* oblivionMod = converter.getOblivionFile();
	TES5File* skyrimMod = converter.getGeckFile();
	TES5File* skyblivion = converter.getSkyblivionFile();
	std::vector<Record*, std::allocator<Record*>> activators;
	std::vector<Record*, std::allocator<Record*>> skyrimActivators;
	std::vector<Record*, std::allocator<Record*>> modActivators;
	oblivionMod->ACTI.pool.MakeRecordsVector(activators);
	skyblivion->ACTI.pool.MakeRecordsVector(skyrimActivators);
	skyrimMod->ACTI.pool.MakeRecordsVector(skyrimActivators);
	
	std::vector<Sk::ACTIRecord*> targets = std::vector<Sk::ACTIRecord*>();
	printer("%d ACTIs found in oblivion file.\n", activators.size());
	for(uint32_t it = 0; it < activators.size(); ++it) {
		Ob::ACTIRecord *p = (Ob::ACTIRecord*)activators[it];

		if (p->SCRI.IsLoaded()) {
			Sk::ACTIRecord* target = reinterpret_cast<Sk::ACTIRecord*>(*std::find_if(skyrimActivators.begin(), skyrimActivators.end(), [=](const Record* record) { return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); }));
			if(!target)
			{
				std::cout << "Cannot find ACTI EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}

			//Find the script
			Ob::SCPTRecord* script = reinterpret_cast<Ob::SCPTRecord*>(*std::find_if(converter.getScripts().begin(), converter.getScripts().end(), [=](const Record* record) { return record->formID == p->SCRI.value;  }));

			try {
				Script* convertedScript = converter.createVirtualMachineScriptFor(script);

				target->VMAD = VMADRecord();
				target->VMAD.scripts.push_back(convertedScript);
				target->IsChanged(true); //Hack - idk why it doesn't mark itself..
				targets.push_back(target);
			}
			catch (std::exception &ex) {
				std::cout << "Cannot bind script to ACTI: " + std::string(ex.what()) << std::endl;
				continue; //Cannot find - thats fine
			}

		}

	}


	for (uint32_t i = 0; i < targets.size(); i++) {
		skyrimMod->ACTI.pool.construct(targets.at(i), NULL, false);
	}

	//TODO:
	//a) IsChanged flag should be passed on in copy constructor
	//b) It should be automatically marked when changing fields ( requires encapsulation of input to records )
	skyrimMod->ACTI.pool.MakeRecordsVector(modActivators);

	for (uint32_t i = 0; i < modActivators.size(); i++) {
			Sk::ACTIRecord* acti = (Sk::ACTIRecord*) modActivators.at(i);
			acti->IsChanged(true);
	}

}

void convertCONT(SkyblivionConverter &converter) {
	TES4File* oblivionMod = converter.getOblivionFile();
	TES5File* skyrimMod = converter.getGeckFile();
	TES5File* skyblivion = converter.getSkyblivionFile();
	std::vector<Record*, std::allocator<Record*>> contvators;
	std::vector<Record*, std::allocator<Record*>> skyrimActivators;
	std::vector<Record*, std::allocator<Record*>> modActivators;
	oblivionMod->CONT.pool.MakeRecordsVector(contvators);
	skyblivion->CONT.pool.MakeRecordsVector(skyrimActivators);
	skyrimMod->CONT.pool.MakeRecordsVector(skyrimActivators);
	std::vector<Sk::CONTRecord*> targets = std::vector<Sk::CONTRecord*>();
	printer("%d CONTs found in oblivion file.\n", contvators.size());
	for (uint32_t it = 0; it < contvators.size(); ++it) {
		Ob::CONTRecord *p = (Ob::CONTRecord*)contvators[it];

		if (p->SCRI.IsLoaded()) {
			Sk::CONTRecord* target = reinterpret_cast<Sk::CONTRecord*>(*std::find_if(skyrimActivators.begin(), skyrimActivators.end(), [=](const Record* record) { return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); }));
			if(!target)
			{
				std::cout << "Cannot find CONT EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}

			//Find the script
			Ob::SCPTRecord* script = reinterpret_cast<Ob::SCPTRecord*>(*std::find_if(converter.getScripts().begin(), converter.getScripts().end(), [=](const Record* record) { return record->formID == p->SCRI.value;  }));

			try {
				Script* convertedScript = converter.createVirtualMachineScriptFor(script);

				target->VMAD = VMADRecord();
				target->VMAD.scripts.push_back(convertedScript);
				target->IsChanged(true); //Hack - idk why it doesn't mark itself..
				targets.push_back(target);
			}
			catch (std::exception &ex) {
				std::cout << "Cannot bind script to CONT: " + std::string(ex.what()) << std::endl;
				continue; //Cannot find - thats fine
			}

		}

	}


	for (uint32_t i = 0; i < targets.size(); i++) {
		skyrimMod->CONT.pool.construct(targets.at(i), NULL, false);
	}


	//TODO:
	//a) IsChanged flag should be passed on in copy constructor
	//b) It should be automatically marked when changing fields ( requires encapsulation of input to records )
	skyrimMod->CONT.pool.MakeRecordsVector(modActivators);

	for (uint32_t i = 0; i < modActivators.size(); i++) {
			Sk::CONTRecord* acti = (Sk::CONTRecord*) modActivators.at(i);
			acti->IsChanged(true);
	}
	


}


void convertDOOR(SkyblivionConverter &converter) {
	TES4File* oblivionMod = converter.getOblivionFile();
	TES5File* skyrimMod = converter.getGeckFile();
	TES5File* skyblivion = converter.getSkyblivionFile();
	std::vector<Record*, std::allocator<Record*>> Doors;
	std::vector<Record*, std::allocator<Record*>> skyrimDoors;
	std::vector<Record*, std::allocator<Record*>> modDoors;
	oblivionMod->DOOR.pool.MakeRecordsVector(Doors);
	skyblivion->DOOR.pool.MakeRecordsVector(skyrimDoors);
	skyrimMod->DOOR.pool.MakeRecordsVector(skyrimDoors);
	std::vector<Sk::DOORRecord*> targets = std::vector<Sk::DOORRecord*>();
	printer("%d DOORs found in oblivion file.\n", Doors.size());
	for (uint32_t it = 0; it < Doors.size(); ++it) {
		Ob::DOORRecord *p = (Ob::DOORRecord*)Doors[it];

		if (p->SCRI.IsLoaded()) {
			Sk::DOORRecord* target = reinterpret_cast<Sk::DOORRecord*>(*std::find_if(skyrimDoors.begin(), skyrimDoors.end(), [=](const Record* record) { return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); }));
			if(!target)
			{
				std::cout << "Cannot find DOOR EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}

			//Find the script
			Ob::SCPTRecord* script = reinterpret_cast<Ob::SCPTRecord*>(*std::find_if(converter.getScripts().begin(), converter.getScripts().end(), [=](const Record* record) { return record->formID == p->SCRI.value;  }));

			try {
				Script* convertedScript = converter.createVirtualMachineScriptFor(script);

				target->VMAD = VMADRecord();
				target->VMAD.scripts.push_back(convertedScript);
				target->IsChanged(true); //Hack - idk why it doesn't mark itself..
				targets.push_back(target);
			}
			catch (std::exception &ex) {
				std::cout << "Cannot bind script to DOOR: " + std::string(ex.what()) << std::endl;
				continue; //Cannot find - thats fine
			}

		}

	}


	for (uint32_t i = 0; i < targets.size(); i++) {
		skyrimMod->DOOR.pool.construct(targets.at(i), NULL, false);
	}

	//TODO:
	//a) IsChanged flag should be passed on in copy constructor
	//b) It should be automatically marked when changing fields ( requires encapsulation of input to records )
	skyrimMod->DOOR.pool.MakeRecordsVector(modDoors);

	for (uint32_t i = 0; i < modDoors.size(); i++) {
			Sk::DOORRecord* acti = (Sk::DOORRecord*) modDoors.at(i);
			acti->IsChanged(true);
	}
	
}

void convertNPC_(SkyblivionConverter &converter) {
	TES4File* oblivionMod = converter.getOblivionFile();
	TES5File* skyrimMod = converter.getGeckFile();
	TES5File* skyblivion = converter.getSkyblivionFile();
	std::vector<Record*, std::allocator<Record*>> Npcs;
	std::vector<Record*, std::allocator<Record*>> Creatures;
	std::vector<Record*, std::allocator<Record*>> skyrimNpcs;
	std::vector<Record*, std::allocator<Record*>> modNpcs;
	oblivionMod->NPC_.pool.MakeRecordsVector(Npcs);
	oblivionMod->CREA.pool.MakeRecordsVector(Creatures);
	skyblivion->NPC_.pool.MakeRecordsVector(skyrimNpcs);
	skyrimMod->NPC_.pool.MakeRecordsVector(skyrimNpcs);
	std::vector<Sk::NPC_Record*> targets = std::vector<Sk::NPC_Record*>();
	printer("%d NPCs found in oblivion file.\n", Npcs.size());
	for (uint32_t it = 0; it < Npcs.size(); ++it) {
		Ob::NPC_Record *p = (Ob::NPC_Record*)Npcs[it];


		if (p->SCRI.IsLoaded()) {
			Sk::NPC_Record* target = reinterpret_cast<Sk::NPC_Record*>(*std::find_if(skyrimNpcs.begin(), skyrimNpcs.end(), [=](const Record* record) { return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); }));
			if(!target)
			{
				std::cout << "Cannot find NPC_ EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}

			//Find the script
			Ob::SCPTRecord* script = reinterpret_cast<Ob::SCPTRecord*>(*std::find_if(converter.getScripts().begin(), converter.getScripts().end(), [=](const Record* record) { return record->formID == p->SCRI.value;  }));

			try {
				Script* convertedScript = converter.createVirtualMachineScriptFor(script);

				target->VMAD = VMADRecord();
				target->VMAD.scripts.push_back(convertedScript);
				target->IsChanged(true); //Hack - idk why it doesn't mark itself..
				targets.push_back(target);
			}
			catch (std::exception &ex) {
				std::cout << "Cannot bind script to NPC_: " + std::string(ex.what()) << std::endl;
				continue; //Cannot find - thats fine
			}

		}

	}

	for (uint32_t it = 0; it < Creatures.size(); ++it) {
		Ob::CREARecord *p = (Ob::CREARecord*)Creatures[it];

		if (p->SCRI.IsLoaded()) {
			Sk::NPC_Record* target = reinterpret_cast<Sk::NPC_Record*>(*std::find_if(skyrimNpcs.begin(), skyrimNpcs.end(), [=](const Record* record) { return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); }));
			if(!target)
			{
				std::cout << "Cannot find NPC_ ( old CREA ) EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}

			//Find the script
			Ob::SCPTRecord* script = reinterpret_cast<Ob::SCPTRecord*>(*std::find_if(converter.getScripts().begin(), converter.getScripts().end(), [=](const Record* record) { return record->formID == p->SCRI.value;  }));

			try {
				Script* convertedScript = converter.createVirtualMachineScriptFor(script);

				target->VMAD = VMADRecord();
				target->VMAD.scripts.push_back(convertedScript);
				target->IsChanged(true); //Hack - idk why it doesn't mark itself..
				targets.push_back(target);
			}
			catch (std::exception &ex) {
				std::cout << "Cannot bind script to NPC_: " + std::string(ex.what()) << std::endl;
				continue; //Cannot find - thats fine
			}

		}

	}



	for (uint32_t i = 0; i < targets.size(); i++) {
		skyrimMod->NPC_.pool.construct(targets.at(i), NULL, false);
	}

	//TODO:
	//a) IsChanged flag should be passed on in copy constructor
	//b) It should be automatically marked when changing fields ( requires encapsulation of input to records )
	skyrimMod->NPC_.pool.MakeRecordsVector(modNpcs);

	for (uint32_t i = 0; i < modNpcs.size(); i++) {
			Sk::NPC_Record* acti = (Sk::NPC_Record*) modNpcs.at(i);
			acti->IsChanged(true);
	}
	

}


void convertWEAP(SkyblivionConverter &converter) {
	TES4File* oblivionMod = converter.getOblivionFile();
	TES5File* skyrimMod = converter.getGeckFile();
	TES5File* skyblivion = converter.getSkyblivionFile();
	std::vector<Record*, std::allocator<Record*>> weapvators;
	std::vector<Record*, std::allocator<Record*>> skyrimActivators;
	std::vector<Record*, std::allocator<Record*>> modActivators;
	oblivionMod->WEAP.pool.MakeRecordsVector(weapvators);	
	skyblivion->WEAP.pool.MakeRecordsVector(skyrimActivators);
	skyrimMod->WEAP.pool.MakeRecordsVector(skyrimActivators);
	std::vector<Sk::WEAPRecord*> targets = std::vector<Sk::WEAPRecord*>();
	printer("%d WEAPs found in oblivion file.\n", weapvators.size());
	for (uint32_t it = 0; it < weapvators.size(); ++it) {
		Ob::WEAPRecord *p = (Ob::WEAPRecord*)weapvators[it];

		if (p->SCRI.IsLoaded()) {
			Sk::WEAPRecord* target = reinterpret_cast<Sk::WEAPRecord*>(*std::find_if(skyrimActivators.begin(), skyrimActivators.end(), [=](const Record* record) { return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); }));
			if(!target)
			{
				std::cout << "Cannot find WEAP EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}

			//Find the script
			Ob::SCPTRecord* script = reinterpret_cast<Ob::SCPTRecord*>(*std::find_if(converter.getScripts().begin(), converter.getScripts().end(), [=](const Record* record) { return record->formID == p->SCRI.value;  }));

			try {
				Script* convertedScript = converter.createVirtualMachineScriptFor(script);

				target->VMAD = VMADRecord();
				target->VMAD.scripts.push_back(convertedScript);
				target->IsChanged(true); //Hack - idk why it doesn't mark itself..
				targets.push_back(target);
			}
			catch (std::exception &ex) {
				std::cout << "Cannot bind script to WEAP: " + std::string(ex.what()) << std::endl;
				continue; //Cannot find - thats fine
			}

		}

	}


	for (uint32_t i = 0; i < targets.size(); i++) {
		skyrimMod->WEAP.pool.construct(targets.at(i), NULL, false);
	}


	//TODO:
	//a) IsChanged flag should be passed on in copy constructor
	//b) It should be automatically marked when changing fields ( requires encapsulation of input to records )
	skyrimMod->WEAP.pool.MakeRecordsVector(modActivators);

	for (uint32_t i = 0; i < modActivators.size(); i++) {
			Sk::WEAPRecord* acti = (Sk::WEAPRecord*) modActivators.at(i);
			acti->IsChanged(true);
	}

}

int main(int argc, char * argv[]) {

	char* input = "Input.esm";
	char* output = "Output.esp";
	char* inputModName = "myMod";

	if (argc < 4) {
		std::cout << "usage: GECKFrontend.exe <input folder> <output folder> <scripts folder>";
		return 0;
	}

	Collection oblivionCollection = Collection(argv[1], 0);
	Collection skyrimCollection = Collection(argv[2], 3);

	ModFlags obFlags = ModFlags(2);
	TES4File* oblivionMod = (TES4File*)oblivionCollection.AddMod("Oblivion.esm", obFlags);

	ModFlags masterFlags = ModFlags(0xA);
	ModFlags skyblivionFlags = ModFlags(0xA);
	skyrimCollection.AddMod("Skyrim.esm", masterFlags);
	TES5File* skyblivion = (TES5File*)skyrimCollection.AddMod("Skyblivion.esm", skyblivionFlags);

	ModFlags espFlags = ModFlags(0x1818);
	TES5File* skyrimMod = (TES5File*)skyrimCollection.AddMod("GECK.esp", espFlags);
	skyrimMod->TES4.MAST.push_back("Skyrim.esm");
	skyrimMod->TES4.MAST.push_back("Skyblivion.esm");
	skyrimMod->TES4.formVersion = 43;

	oblivionCollection.Load();
	skyrimCollection.Load();

	SkyblivionConverter converter = SkyblivionConverter(oblivionCollection, skyrimCollection, std::string(argv[3]));

	std::cout << "Converting QUST records.. " << std::endl;
	std::vector<Sk::QUSTRecord *> *resQUST = converter.convertQUSTFromOblivion();
	std::cout << "Converting DIAL records.. " << std::endl;
	std::vector<Sk::DIALRecord *> *resDIAL = converter.convertDIALFromOblivion();

	std::cout << "Converting PACK records.. " << std::endl;
	std::vector<Record*, std::allocator<Record*>> packages;
	oblivionMod->PACK.pool.MakeRecordsVector(packages);

	int count = packages.size();

	int i = 0;
	for (uint32_t it = 0; it < packages.size(); ++it) {
		Ob::PACKRecord *p = (Ob::PACKRecord*)packages[it];

		try {
			Sk::PACKRecord* skPack = new Sk::PACKRecord();
			converter.convertPACKFromOblivion(*p, *skPack);
			skyrimMod->PACK.pool.construct(skPack, NULL, false);
		}
		catch (std::exception &e) {
			printer(e.what());
			printer("\r\n");
			continue;
		}

		++i;
	}


	/*
	 * Index new EDIDs and formids
	 */
	for (uint32_t it = 0; it < resQUST->size(); ++it) {
		Sk::QUSTRecord *qust = (Sk::QUSTRecord*)(*resQUST)[it];
		std::string qustEdid = std::string(qust->EDID.value);
		std::transform(qustEdid.begin(), qustEdid.end(), qustEdid.begin(), ::tolower);
		converter.insertToEdidMap(qustEdid, qust->formID);
	}

	/**
	 * @todo - How we handle topics splitted into N dialogue topics and suffixed by QSTI value?
	 */
	for (uint32_t it = 0; it < resDIAL->size(); ++it) {
		Sk::DIALRecord *dial = (Sk::DIALRecord*)(*resDIAL)[it];
		std::string dialEdid = std::string(dial->EDID.value);
		std::transform(dialEdid.begin(), dialEdid.end(), dialEdid.begin(), ::tolower);
		converter.insertToEdidMap(dialEdid, dial->formID);
	}

	std::cout << "Binding VMADs to ACTI records.. " << std::endl;
	convertACTI(converter);
	std::cout << "Binding VMADs to CONT records.. " << std::endl;
	convertCONT(converter);
	std::cout << "Binding VMADs to DOOR records.. " << std::endl;
	convertDOOR(converter);
	std::cout << "Binding VMADs to NPC_ records.. " << std::endl;
	convertNPC_(converter);
	std::cout << "Binding VMADs to WEAP records.. " << std::endl;
	convertWEAP(converter);

    SaveFlags skSaveFlags = SaveFlags(2);

    skyrimCollection.SaveMod((ModFile*&)skyrimMod, skSaveFlags, "GECK.esp");

    return 0;

}

