#include <sstream>
#include <iostream>
#include <boost/regex.hpp>
#include "CBash/src/Skyblivion/Skyblivion.h"

using namespace Skyblivion;

void convertACTI(SkyblivionConverter &converter) {
	TES4File* oblivionMod = converter.getOblivionFile();
	TES5File* skyrimMod = converter.getGeckFile();
	TES5File* skyblivion = converter.getSkyblivionFile();
	std::vector<Record*, std::allocator<Record*>> obRecords;
	std::vector<Record*, std::allocator<Record*>> skbRecords;
	std::vector<Record*, std::allocator<Record*>> modRecords;
	oblivionMod->ACTI.pool.MakeRecordsVector(obRecords);
	skyblivion->ACTI.pool.MakeRecordsVector(skbRecords);
	skyrimMod->ACTI.pool.MakeRecordsVector(skbRecords);
	
	std::vector<Sk::ACTIRecord*> targets = std::vector<Sk::ACTIRecord*>();
	log_debug << obRecords.size() << " ACTIs found in oblivion file.\n";
	for(uint32_t it = 0; it < obRecords.size(); ++it) {
		Ob::ACTIRecord *p = (Ob::ACTIRecord*)obRecords[it];

		if (p->SCRI.IsLoaded()) {
			auto foundRec = std::find_if(skbRecords.begin(), skbRecords.end(), [=](const Record* record) {return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); });
			if (foundRec == skbRecords.end())
			{
				log_error << "Cannot find ACTI EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}
			Sk::ACTIRecord* target = reinterpret_cast<Sk::ACTIRecord*>(*foundRec);

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
				log_error << "Cannot bind script to ACTI: " + std::string(ex.what()) << std::endl;
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
	skyrimMod->ACTI.pool.MakeRecordsVector(modRecords);

	for (uint32_t i = 0; i < modRecords.size(); i++) {
			Sk::ACTIRecord* acti = (Sk::ACTIRecord*) modRecords.at(i);
			acti->IsChanged(true);
	}

}

void convertCONT(SkyblivionConverter &converter) {
	TES4File* oblivionMod = converter.getOblivionFile();
	TES5File* skyrimMod = converter.getGeckFile();
	TES5File* skyblivion = converter.getSkyblivionFile();
	std::vector<Record*, std::allocator<Record*>> obRecords;
	std::vector<Record*, std::allocator<Record*>> skbRecords;
	std::vector<Record*, std::allocator<Record*>> modRecords;
	oblivionMod->CONT.pool.MakeRecordsVector(obRecords);
	skyblivion->CONT.pool.MakeRecordsVector(skbRecords);
	skyrimMod->CONT.pool.MakeRecordsVector(skbRecords);
	std::vector<Sk::CONTRecord*> targets = std::vector<Sk::CONTRecord*>();
	log_debug << obRecords.size() << " CONTs found in oblivion file.\n";
	for (uint32_t it = 0; it < obRecords.size(); ++it) {
		Ob::CONTRecord *p = (Ob::CONTRecord*)obRecords[it];

		if (p->SCRI.IsLoaded()) {
			auto foundRec = std::find_if(skbRecords.begin(), skbRecords.end(), [=](const Record* record) {return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); });
			if (foundRec == skbRecords.end())
			{
				log_error << "Cannot find CONT EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}
			Sk::CONTRecord* target = reinterpret_cast<Sk::CONTRecord*>(*foundRec);

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
				log_error << "Cannot bind script to CONT: " + std::string(ex.what()) << std::endl;
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
	skyrimMod->CONT.pool.MakeRecordsVector(modRecords);

	for (uint32_t i = 0; i < modRecords.size(); i++) {
			Sk::CONTRecord* acti = (Sk::CONTRecord*) modRecords.at(i);
			acti->IsChanged(true);
	}
	


}

void convertDOOR(SkyblivionConverter &converter) {
	TES4File* oblivionMod = converter.getOblivionFile();
	TES5File* skyrimMod = converter.getGeckFile();
	TES5File* skyblivion = converter.getSkyblivionFile();
	std::vector<Record*, std::allocator<Record*>> obRecords;
	std::vector<Record*, std::allocator<Record*>> skbRecords;
	std::vector<Record*, std::allocator<Record*>> modRecords;
	oblivionMod->DOOR.pool.MakeRecordsVector(obRecords);
	skyblivion->DOOR.pool.MakeRecordsVector(skbRecords);
	skyrimMod->DOOR.pool.MakeRecordsVector(skbRecords);
	std::vector<Sk::DOORRecord*> targets = std::vector<Sk::DOORRecord*>();
	log_debug << obRecords.size() << " DOORs found in oblivion file.\n";
	for (uint32_t it = 0; it < obRecords.size(); ++it) {
		Ob::DOORRecord *p = (Ob::DOORRecord*)obRecords[it];

		if (p->SCRI.IsLoaded()) {
			auto foundRec = std::find_if(skbRecords.begin(), skbRecords.end(), [=](const Record* record) {return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); });
			if (foundRec == skbRecords.end())
			{
				log_error << "Cannot find DOOR EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}
			Sk::DOORRecord* target = reinterpret_cast<Sk::DOORRecord*>(*foundRec);

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
				log_error << "Cannot bind script to DOOR: " + std::string(ex.what()) << std::endl;
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
	skyrimMod->DOOR.pool.MakeRecordsVector(modRecords);

	for (uint32_t i = 0; i < modRecords.size(); i++) {
			Sk::DOORRecord* acti = (Sk::DOORRecord*) modRecords.at(i);
			acti->IsChanged(true);
	}
	
}

void convertNPC_(SkyblivionConverter &converter) {
	TES4File* oblivionMod = converter.getOblivionFile();
	TES5File* skyrimMod = converter.getGeckFile();
	TES5File* skyblivion = converter.getSkyblivionFile();
	std::vector<Record*, std::allocator<Record*>> obRecords;
	std::vector<Record*, std::allocator<Record*>> Creatures;
	std::vector<Record*, std::allocator<Record*>> LeveledCrea;
	std::vector<Record*, std::allocator<Record*>> skbRecords;
	std::vector<Record*, std::allocator<Record*>> modRecords;
	oblivionMod->NPC_.pool.MakeRecordsVector(obRecords);
	oblivionMod->CREA.pool.MakeRecordsVector(Creatures);
	oblivionMod->LVLC.pool.MakeRecordsVector(LeveledCrea);
	skyblivion->NPC_.pool.MakeRecordsVector(skbRecords);
	skyrimMod->NPC_.pool.MakeRecordsVector(skbRecords);
	std::vector<Sk::NPC_Record*> targets = std::vector<Sk::NPC_Record*>();
	log_debug << obRecords.size() << " NPCs found in oblivion file.\n";
	for (uint32_t it = 0; it < obRecords.size(); ++it) {
		Ob::NPC_Record *p = (Ob::NPC_Record*)obRecords[it];


		if (p->SCRI.IsLoaded()) {
			auto foundRec = std::find_if(skbRecords.begin(), skbRecords.end(), [=](const Record* record) {return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); });
			if (foundRec == skbRecords.end())
			{
				log_error << "Cannot find NPC_ EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}
			Sk::NPC_Record* target = reinterpret_cast<Sk::NPC_Record*>(*foundRec);

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
				log_error << "Cannot bind script to NPC_: " + std::string(ex.what()) << std::endl;
				continue; //Cannot find - thats fine
			}

		}

	}

	log_debug << Creatures.size() << " CREAs found in oblivion file.\n";
	for (uint32_t it = 0; it < Creatures.size(); ++it) {
		Ob::CREARecord *p = (Ob::CREARecord*)Creatures[it];

		if (p->SCRI.IsLoaded()) {
			auto foundRec = std::find_if(skbRecords.begin(), skbRecords.end(), [=](const Record* record) {return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); });
			if (foundRec == skbRecords.end())
			{
				log_error << "Cannot find NPC_ ( old CREA ) EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}
			Sk::NPC_Record* target = reinterpret_cast<Sk::NPC_Record*>(*foundRec);

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
				log_error << "Cannot bind script to NPC_: " + std::string(ex.what()) << std::endl;
				continue; //Cannot find - thats fine
			}

		}

	}

	log_debug << LeveledCrea.size() << " LVLCs found in oblivion file.\n";
	for (uint32_t it = 0; it < LeveledCrea.size(); ++it) {
		Ob::LVLCRecord *p = (Ob::LVLCRecord*)LeveledCrea[it];
		if (p->SCRI.IsLoaded()) {
			std::string lvlnEdid = "TES4" + std::string(p->EDID.value);
			std::transform(lvlnEdid.begin(), lvlnEdid.end(), lvlnEdid.begin(), ::tolower);
			FORMID lvlnFormid = converter.findRecordFormidByEDID(lvlnEdid);
			if (lvlnFormid == NULL) {
				log_error << "Cannot find LVLN  EDID " << lvlnEdid << std::endl;
				continue;
			}

			auto foundRec = std::find_if(skbRecords.begin(), skbRecords.end(), [=](const Record* record) { return (lvlnFormid & 0x00FFFFFF) == (((Sk::NPC_Record*)record)->TPLT.value & 0x00FFFFFF); });
			if (foundRec == skbRecords.end())
			{
				log_warning << "Cannot find NPC_, LVLN EDID " << lvlnEdid << " LVLN formid (NPC_->TPLT) " << lvlnFormid << std::endl;
				continue;
			}
			Sk::NPC_Record* target = reinterpret_cast<Sk::NPC_Record*>(*foundRec);
			//Find the script
			Ob::SCPTRecord* script = reinterpret_cast<Ob::SCPTRecord*>(*std::find_if(converter.getScripts().begin(), converter.getScripts().end(), [=](const Record* record) { return record->formID == p->SCRI.value;  }));

			try {
				Script* convertedScript = converter.createVirtualMachineScriptFor(script);

				// Do not override if there are already scripts in VMAD record
				if (target->VMAD.scripts.size() < 1)
					target->VMAD = VMADRecord();

				target->VMAD.scripts.push_back(convertedScript);
				target->IsChanged(true); //Hack - idk why it doesn't mark itself..
				targets.push_back(target);
			}
			catch (std::exception &ex) {
				log_error << "Cannot bind script to NPC_: " + std::string(ex.what()) << std::endl;
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
	skyrimMod->NPC_.pool.MakeRecordsVector(modRecords);

	for (uint32_t i = 0; i < modRecords.size(); i++) {
			Sk::NPC_Record* acti = (Sk::NPC_Record*) modRecords.at(i);
			acti->IsChanged(true);
	}
	

}

void convertWEAP(SkyblivionConverter &converter) {
	TES4File* oblivionMod = converter.getOblivionFile();
	TES5File* skyrimMod = converter.getGeckFile();
	TES5File* skyblivion = converter.getSkyblivionFile();
	std::vector<Record*, std::allocator<Record*>> obRecords;
	std::vector<Record*, std::allocator<Record*>> skbRecords;
	std::vector<Record*, std::allocator<Record*>> modRecords;
	oblivionMod->WEAP.pool.MakeRecordsVector(obRecords);
	skyblivion->WEAP.pool.MakeRecordsVector(skbRecords);
	skyrimMod->WEAP.pool.MakeRecordsVector(skbRecords);
	std::vector<Sk::WEAPRecord*> targets = std::vector<Sk::WEAPRecord*>();
	log_debug << obRecords.size() << " WEAPs found in oblivion file.\n";
	for (uint32_t it = 0; it < obRecords.size(); ++it) {
		Ob::WEAPRecord *p = (Ob::WEAPRecord*)obRecords[it];

		if (p->SCRI.IsLoaded()) {
			auto foundRec = std::find_if(skbRecords.begin(), skbRecords.end(), [=](const Record* record) {return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); });
			if (foundRec == skbRecords.end())
			{
				log_error << "Cannot find WEAP EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}
			Sk::WEAPRecord* target = reinterpret_cast<Sk::WEAPRecord*>(*foundRec);

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
				log_error << "Cannot bind script to WEAP: " + std::string(ex.what()) << std::endl;
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
	skyrimMod->WEAP.pool.MakeRecordsVector(modRecords);

	for (uint32_t i = 0; i < modRecords.size(); i++) {
			Sk::WEAPRecord* acti = (Sk::WEAPRecord*) modRecords.at(i);
			acti->IsChanged(true);
	}

}

void convertARMO(SkyblivionConverter &converter) {
	TES4File* oblivionMod = converter.getOblivionFile();
	TES5File* skyrimMod = converter.getGeckFile();
	TES5File* skyblivion = converter.getSkyblivionFile();
	std::vector<Record*, std::allocator<Record*>> obRecords;
	std::vector<Record*, std::allocator<Record*>> obClotRecords;
	std::vector<Record*, std::allocator<Record*>> skbRecords;
	std::vector<Record*, std::allocator<Record*>> modRecords;
	oblivionMod->ARMO.pool.MakeRecordsVector(obRecords);
	oblivionMod->CLOT.pool.MakeRecordsVector(obClotRecords);
	skyblivion->ARMO.pool.MakeRecordsVector(skbRecords);
	skyrimMod->ARMO.pool.MakeRecordsVector(skbRecords);
	std::vector<Sk::ARMORecord*> targets = std::vector<Sk::ARMORecord*>();
	log_debug << obRecords.size() << " ARMOs found in oblivion file.\n";
	for (uint32_t it = 0; it < obRecords.size(); ++it) {
		Ob::ARMORecord *p = (Ob::ARMORecord*)obRecords[it];

		if (p->SCRI.IsLoaded()) {
			auto foundRec = std::find_if(skbRecords.begin(), skbRecords.end(), [=](const Record* record) {return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); });
			if (foundRec == skbRecords.end())
			{
				log_error << "Cannot find ARMO EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}
			Sk::ARMORecord* target = reinterpret_cast<Sk::ARMORecord*>(*foundRec);

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
				log_error << "Cannot bind script to ARMO: " + std::string(ex.what()) << std::endl;
				continue; //Cannot find - thats fine
			}

		}

	}

	log_debug << obRecords.size() << " CLOTs found in oblivion file.\n";
	for (uint32_t it = 0; it < obClotRecords.size(); ++it) {
		Ob::CLOTRecord *p = (Ob::CLOTRecord*)obClotRecords[it];

		if (p->SCRI.IsLoaded()) {
			auto foundRec = std::find_if(skbRecords.begin(), skbRecords.end(), [=](const Record* record) {return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); });
			if (foundRec == skbRecords.end())
			{
				log_error << "Cannot find ARMO (old CLOT) EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}
			Sk::ARMORecord* target = reinterpret_cast<Sk::ARMORecord*>(*foundRec);

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
				log_error << "Cannot bind script to ARMO: " + std::string(ex.what()) << std::endl;
				continue; //Cannot find - thats fine
			}

		}

	}


	for (uint32_t i = 0; i < targets.size(); i++) {
		skyrimMod->ARMO.pool.construct(targets.at(i), NULL, false);
	}


	//TODO:
	//a) IsChanged flag should be passed on in copy constructor
	//b) It should be automatically marked when changing fields ( requires encapsulation of input to records )
	skyrimMod->ARMO.pool.MakeRecordsVector(modRecords);

	for (uint32_t i = 0; i < modRecords.size(); i++) {
		Sk::ARMORecord* acti = (Sk::ARMORecord*) modRecords.at(i);
		acti->IsChanged(true);
	}

}

void convertBOOK(SkyblivionConverter &converter) {
	TES4File* oblivionMod = converter.getOblivionFile();
	TES5File* skyrimMod = converter.getGeckFile();
	TES5File* skyblivion = converter.getSkyblivionFile();
	std::vector<Record*, std::allocator<Record*>> obRecords;
	std::vector<Record*, std::allocator<Record*>> skbRecords;
	std::vector<Record*, std::allocator<Record*>> modRecords;
	oblivionMod->BOOK.pool.MakeRecordsVector(obRecords);
	skyblivion->BOOK.pool.MakeRecordsVector(skbRecords);
	skyrimMod->BOOK.pool.MakeRecordsVector(skbRecords);
	std::vector<Sk::BOOKRecord*> targets = std::vector<Sk::BOOKRecord*>();
	log_debug << obRecords.size() << " BOOKs found in oblivion file.\n";
	for (uint32_t it = 0; it < obRecords.size(); ++it) {
		Ob::BOOKRecord *p = (Ob::BOOKRecord*)obRecords[it];

		if (p->SCRI.IsLoaded()) {
			auto foundRec = std::find_if(skbRecords.begin(), skbRecords.end(), [=](const Record* record) {return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); });
			if (foundRec == skbRecords.end())
			{
				log_error << "Cannot find BOOK EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}
			Sk::BOOKRecord* target = reinterpret_cast<Sk::BOOKRecord*>(*foundRec);

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
				log_error << "Cannot bind script to BOOK: " + std::string(ex.what()) << std::endl;
				continue; //Cannot find - thats fine
			}

		}

	}


	for (uint32_t i = 0; i < targets.size(); i++) {
		skyrimMod->BOOK.pool.construct(targets.at(i), NULL, false);
	}


	//TODO:
	//a) IsChanged flag should be passed on in copy constructor
	//b) It should be automatically marked when changing fields ( requires encapsulation of input to records )
	skyrimMod->BOOK.pool.MakeRecordsVector(modRecords);

	for (uint32_t i = 0; i < modRecords.size(); i++) {
		Sk::BOOKRecord* acti = (Sk::BOOKRecord*) modRecords.at(i);
		acti->IsChanged(true);
	}

}

void convertINGR(SkyblivionConverter &converter) {
	TES4File* oblivionMod = converter.getOblivionFile();
	TES5File* skyrimMod = converter.getGeckFile();
	TES5File* skyblivion = converter.getSkyblivionFile();
	std::vector<Record*, std::allocator<Record*>> obRecords;
	std::vector<Record*, std::allocator<Record*>> skbRecords;
	std::vector<Record*, std::allocator<Record*>> modRecords;
	oblivionMod->INGR.pool.MakeRecordsVector(obRecords);
	skyblivion->INGR.pool.MakeRecordsVector(skbRecords);
	skyrimMod->INGR.pool.MakeRecordsVector(skbRecords);
	std::vector<Sk::INGRRecord*> targets = std::vector<Sk::INGRRecord*>();
	log_debug << obRecords.size() << " INGRs found in oblivion file.\n";
	for (uint32_t it = 0; it < obRecords.size(); ++it) {
		Ob::INGRRecord *p = (Ob::INGRRecord*)obRecords[it];

		if (p->SCRI.IsLoaded()) {
			auto foundRec = std::find_if(skbRecords.begin(), skbRecords.end(), [=](const Record* record) {return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); });
			if (foundRec == skbRecords.end())
			{
				log_error << "Cannot find INGR EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}
			Sk::INGRRecord* target = reinterpret_cast<Sk::INGRRecord*>(*foundRec);

			//Find the script
			Ob::SCPTRecord* script = reinterpret_cast<Ob::SCPTRecord*>(*std::find_if(converter.getScripts().begin(), converter.getScripts().end(), [=](const Record* record) { return record->formID == p->SCRI.value;  }));

			try {
				Script* convertedScript = converter.createVirtualMachineScriptFor(script);

				target->VMAD = OptSubRecord<VMADRecord>();
				target->VMAD.Load();
				target->VMAD.value->scripts.push_back(convertedScript);
				target->IsChanged(true); //Hack - idk why it doesn't mark itself..
				targets.push_back(target);
			}
			catch (std::exception &ex) {
				log_error << "Cannot bind script to INGR: " + std::string(ex.what()) << std::endl;
				continue; //Cannot find - thats fine
			}

		}

	}


	for (uint32_t i = 0; i < targets.size(); i++) {
		skyrimMod->INGR.pool.construct(targets.at(i), NULL, false);
	}


	//TODO:
	//a) IsChanged flag should be passed on in copy constructor
	//b) It should be automatically marked when changing fields ( requires encapsulation of input to records )
	skyrimMod->INGR.pool.MakeRecordsVector(modRecords);

	for (uint32_t i = 0; i < modRecords.size(); i++) {
		Sk::INGRRecord* acti = (Sk::INGRRecord*) modRecords.at(i);
		acti->IsChanged(true);
	}

}

void convertKEYM(SkyblivionConverter &converter) {
	TES4File* oblivionMod = converter.getOblivionFile();
	TES5File* skyrimMod = converter.getGeckFile();
	TES5File* skyblivion = converter.getSkyblivionFile();
	std::vector<Record*, std::allocator<Record*>> obRecords;
	std::vector<Record*, std::allocator<Record*>> skbRecords;
	std::vector<Record*, std::allocator<Record*>> modRecords;
	oblivionMod->KEYM.pool.MakeRecordsVector(obRecords);
	skyblivion->KEYM.pool.MakeRecordsVector(skbRecords);
	skyrimMod->KEYM.pool.MakeRecordsVector(skbRecords);
	std::vector<Sk::KEYMRecord*> targets = std::vector<Sk::KEYMRecord*>();
	log_debug << obRecords.size() << " KEYMs found in oblivion file.\n";
	for (uint32_t it = 0; it < obRecords.size(); ++it) {
		Ob::KEYMRecord *p = (Ob::KEYMRecord*)obRecords[it];

		if (p->SCRI.IsLoaded()) {
			auto foundRec = std::find_if(skbRecords.begin(), skbRecords.end(), [=](const Record* record) {return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); });
			if (foundRec == skbRecords.end())
			{
				log_error << "Cannot find KEYM EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}
			Sk::KEYMRecord* target = reinterpret_cast<Sk::KEYMRecord*>(*foundRec);

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
				log_error << "Cannot bind script to KEYM: " + std::string(ex.what()) << std::endl;
				continue; //Cannot find - thats fine
			}

		}

	}


	for (uint32_t i = 0; i < targets.size(); i++) {
		skyrimMod->KEYM.pool.construct(targets.at(i), NULL, false);
	}


	//TODO:
	//a) IsChanged flag should be passed on in copy constructor
	//b) It should be automatically marked when changing fields ( requires encapsulation of input to records )
	skyrimMod->KEYM.pool.MakeRecordsVector(modRecords);

	for (uint32_t i = 0; i < modRecords.size(); i++) {
		Sk::KEYMRecord* acti = (Sk::KEYMRecord*) modRecords.at(i);
		acti->IsChanged(true);
	}

}

void convertMISC(SkyblivionConverter &converter) {
	TES4File* oblivionMod = converter.getOblivionFile();
	TES5File* skyrimMod = converter.getGeckFile();
	TES5File* skyblivion = converter.getSkyblivionFile();
	std::vector<Record*, std::allocator<Record*>> obRecords;
	std::vector<Record*, std::allocator<Record*>> obSgstRecords;
	std::vector<Record*, std::allocator<Record*>> skbRecords;
	std::vector<Record*, std::allocator<Record*>> modRecords;
	oblivionMod->MISC.pool.MakeRecordsVector(obRecords);
	oblivionMod->SGST.pool.MakeRecordsVector(obSgstRecords);
	skyblivion->MISC.pool.MakeRecordsVector(skbRecords);
	skyrimMod->MISC.pool.MakeRecordsVector(skbRecords);
	std::vector<Sk::MISCRecord*> targets = std::vector<Sk::MISCRecord*>();
	log_debug << obRecords.size() << " MISCs found in oblivion file.\n";
	for (uint32_t it = 0; it < obRecords.size(); ++it) {
		Ob::MISCRecord *p = (Ob::MISCRecord*)obRecords[it];

		if (p->SCRI.IsLoaded()) {
			auto foundRec = std::find_if(skbRecords.begin(), skbRecords.end(), [=](const Record* record) {return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); });
			if (foundRec == skbRecords.end())
			{
				log_error << "Cannot find MISC EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}
			Sk::MISCRecord* target = reinterpret_cast<Sk::MISCRecord*>(*foundRec);

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
				log_error << "Cannot bind script to MISC: " + std::string(ex.what()) << std::endl;
				continue; //Cannot find - thats fine
			}

		}

	}

	printer("%d SGSTs found in oblivion file.\n", obSgstRecords.size());
	for (uint32_t it = 0; it < obSgstRecords.size(); ++it) {
		Ob::SGSTRecord *p = (Ob::SGSTRecord*)obSgstRecords[it];

		if (p->SCRI.IsLoaded()) {
			auto foundRec = std::find_if(skbRecords.begin(), skbRecords.end(), [=](const Record* record) {return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); });
			if (foundRec == skbRecords.end())
			{
				log_error << "Cannot find MISC (old SGST) EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}
			Sk::MISCRecord* target = reinterpret_cast<Sk::MISCRecord*>(*foundRec);

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
				log_error << "Cannot bind script to MISC: " + std::string(ex.what()) << std::endl;
				continue; //Cannot find - thats fine
			}

		}

	}


	for (uint32_t i = 0; i < targets.size(); i++) {
		skyrimMod->MISC.pool.construct(targets.at(i), NULL, false);
	}


	//TODO:
	//a) IsChanged flag should be passed on in copy constructor
	//b) It should be automatically marked when changing fields ( requires encapsulation of input to records )
	skyrimMod->MISC.pool.MakeRecordsVector(modRecords);

	for (uint32_t i = 0; i < modRecords.size(); i++) {
		Sk::MISCRecord* acti = (Sk::MISCRecord*) modRecords.at(i);
		acti->IsChanged(true);
	}

}

void convertFLOR(SkyblivionConverter &converter) {
	TES4File* oblivionMod = converter.getOblivionFile();
	TES5File* skyrimMod = converter.getGeckFile();
	TES5File* skyblivion = converter.getSkyblivionFile();
	std::vector<Record*, std::allocator<Record*>> obRecords;
	std::vector<Record*, std::allocator<Record*>> skbRecords;
	std::vector<Record*, std::allocator<Record*>> modRecords;
	oblivionMod->FLOR.pool.MakeRecordsVector(obRecords);
	skyblivion->FLOR.pool.MakeRecordsVector(skbRecords);
	skyrimMod->FLOR.pool.MakeRecordsVector(skbRecords);
	std::vector<Sk::FLORRecord*> targets = std::vector<Sk::FLORRecord*>();
	log_debug << obRecords.size() << " FLORs found in oblivion file.\n";
	for (uint32_t it = 0; it < obRecords.size(); ++it) {
		Ob::FLORRecord *p = (Ob::FLORRecord*)obRecords[it];

		if (p->SCRI.IsLoaded()) {
			auto foundRec = std::find_if(skbRecords.begin(), skbRecords.end(), [=](const Record* record) {return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); });
			if (foundRec == skbRecords.end())
			{
				log_error << "Cannot find FLOR EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}
			Sk::FLORRecord* target = reinterpret_cast<Sk::FLORRecord*>(*foundRec);

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
				log_error << "Cannot bind script to FLOR: " + std::string(ex.what()) << std::endl;
				continue; //Cannot find - thats fine
			}

		}

	}


	for (uint32_t i = 0; i < targets.size(); i++) {
		skyrimMod->FLOR.pool.construct(targets.at(i), NULL, false);
	}


	//TODO:
	//a) IsChanged flag should be passed on in copy constructor
	//b) It should be automatically marked when changing fields ( requires encapsulation of input to records )
	skyrimMod->FLOR.pool.MakeRecordsVector(modRecords);

	for (uint32_t i = 0; i < modRecords.size(); i++) {
		Sk::FLORRecord* acti = (Sk::FLORRecord*) modRecords.at(i);
		acti->IsChanged(true);
	}

}

void convertFURN(SkyblivionConverter &converter) {
	TES4File* oblivionMod = converter.getOblivionFile();
	TES5File* skyrimMod = converter.getGeckFile();
	TES5File* skyblivion = converter.getSkyblivionFile();
	std::vector<Record*, std::allocator<Record*>> obRecords;
	std::vector<Record*, std::allocator<Record*>> skbRecords;
	std::vector<Record*, std::allocator<Record*>> modRecords;
	oblivionMod->FURN.pool.MakeRecordsVector(obRecords);
	skyblivion->FURN.pool.MakeRecordsVector(skbRecords);
	skyrimMod->FURN.pool.MakeRecordsVector(skbRecords);
	std::vector<Sk::FURNRecord*> targets = std::vector<Sk::FURNRecord*>();
	log_debug << obRecords.size() << " FURNs found in oblivion file.\n";
	for (uint32_t it = 0; it < obRecords.size(); ++it) {
		Ob::FURNRecord *p = (Ob::FURNRecord*)obRecords[it];

		if (p->SCRI.IsLoaded()) {
			auto foundRec = std::find_if(skbRecords.begin(), skbRecords.end(), [=](const Record* record) {return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); });
			if (foundRec == skbRecords.end())
			{
				log_error << "Cannot find FURN EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}
			Sk::FURNRecord* target = reinterpret_cast<Sk::FURNRecord*>(*foundRec);

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
				log_error << "Cannot bind script to FURN: " + std::string(ex.what()) << std::endl;
				continue; //Cannot find - thats fine
			}

		}

	}


	for (uint32_t i = 0; i < targets.size(); i++) {
		skyrimMod->FURN.pool.construct(targets.at(i), NULL, false);
	}


	//TODO:
	//a) IsChanged flag should be passed on in copy constructor
	//b) It should be automatically marked when changing fields ( requires encapsulation of input to records )
	skyrimMod->FURN.pool.MakeRecordsVector(modRecords);

	for (uint32_t i = 0; i < modRecords.size(); i++) {
		Sk::FURNRecord* acti = (Sk::FURNRecord*) modRecords.at(i);
		acti->IsChanged(true);
	}

}

void convertLIGH(SkyblivionConverter &converter) {
	TES4File* oblivionMod = converter.getOblivionFile();
	TES5File* skyrimMod = converter.getGeckFile();
	TES5File* skyblivion = converter.getSkyblivionFile();
	std::vector<Record*, std::allocator<Record*>> obRecords;
	std::vector<Record*, std::allocator<Record*>> skbRecords;
	std::vector<Record*, std::allocator<Record*>> modRecords;
	oblivionMod->LIGH.pool.MakeRecordsVector(obRecords);
	skyblivion->LIGH.pool.MakeRecordsVector(skbRecords);
	skyrimMod->LIGH.pool.MakeRecordsVector(skbRecords);
	std::vector<Sk::LIGHRecord*> targets = std::vector<Sk::LIGHRecord*>();
	log_debug << obRecords.size() << " LIGHs found in oblivion file.\n";
	for (uint32_t it = 0; it < obRecords.size(); ++it) {
		Ob::LIGHRecord *p = (Ob::LIGHRecord*)obRecords[it];

		if (p->SCRI.IsLoaded()) {
			auto foundRec = std::find_if(skbRecords.begin(), skbRecords.end(), [=](const Record* record) {return (p->formID & 0x00FFFFFF) == (record->formID & 0x00FFFFFF); });
			if (foundRec == skbRecords.end())
			{
				log_error << "Cannot find LIGH EDID " << std::string(p->GetEditorIDKey()) << std::endl;
				continue;
			}
			Sk::LIGHRecord* target = reinterpret_cast<Sk::LIGHRecord*>(*foundRec);

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
				log_error << "Cannot bind script to LIGH: " + std::string(ex.what()) << std::endl;
				continue; //Cannot find - thats fine
			}

		}

	}


	for (uint32_t i = 0; i < targets.size(); i++) {
		skyrimMod->LIGH.pool.construct(targets.at(i), NULL, false);
	}


	//TODO:
	//a) IsChanged flag should be passed on in copy constructor
	//b) It should be automatically marked when changing fields ( requires encapsulation of input to records )
	skyrimMod->LIGH.pool.MakeRecordsVector(modRecords);

	for (uint32_t i = 0; i < modRecords.size(); i++) {
		Sk::LIGHRecord* acti = (Sk::LIGHRecord*) modRecords.at(i);
		acti->IsChanged(true);
	}

}

void addSpeakAsNpcs(SkyblivionConverter &converter, Collection &skyrimCollection) {
	std::string metadataFile = converter.ROOT_BUILD_PATH() + "Metadata";
	std::FILE* scriptHandle = std::fopen(metadataFile.c_str(), "r");
	if (!scriptHandle) {
		log_error << "Couldn't find Metadata File\n";
		return;
	}

	fseek(scriptHandle, 0, SEEK_END);
	size_t size = ftell(scriptHandle);
	char* scriptData = new char[size];
	rewind(scriptHandle);
	fread(scriptData, sizeof(char), size, scriptHandle);
	fclose(scriptHandle);
	std::string fullScript(scriptData);
	delete[] scriptData;

	boost::regex propRegex("ADD_SPEAK_AS_ACTOR (.*?)\\n");

	boost::sregex_iterator properties(fullScript.begin(), fullScript.end(), propRegex, boost::match_not_dot_newline);
	boost::sregex_iterator end;

	std::string colPrefix = "col_";

	TES5File* skyrimMod = converter.getGeckFile();
	ModFile *skyblivionMod = converter.getSkyblivionFile();

	Sk::CELLRecord *newCell = new Sk::CELLRecord();
	newCell->formID = skyrimCollection.NextFreeExpandedFormID(skyblivionMod);

	std::string cellEdid = std::string();
	cellEdid = "TES4SpeakAsHoldingCell";
	char *cstr = new char[cellEdid.length() + 1];
	strncpy(cstr, cellEdid.c_str(), cellEdid.length() + 1);
	newCell->EDID.value = cstr;

	std::vector<std::string> actorNames;

	for (; properties != end; ++properties) {
		std::string actorName = (*properties)[1];

		if (std::find(actorNames.begin(), actorNames.end(), actorName) != actorNames.end())
			continue;

		actorNames.push_back(actorName);

		std::string achrEdid = "TES4" + actorName + "Ref";
		cstr = new char[achrEdid.length() + 1];
		strncpy(cstr, achrEdid.c_str(), achrEdid.length() + 1);
		std::transform(achrEdid.begin(), achrEdid.end(), achrEdid.begin(), ::tolower);

		if (converter.findRecordFormidByEDID(achrEdid) != NULL) {
			log_info << achrEdid << " already exists, new ACHR record won't be created\n";
			continue;
		}

		Sk::ACHRRecord *newAchr = new Sk::ACHRRecord();
		newAchr->formID = skyrimCollection.NextFreeExpandedFormID(skyblivionMod);

		newAchr->EDID.value = cstr;
		newAchr->flags = 0x400;

		std::transform(actorName.begin(), actorName.end(), actorName.begin(), ::tolower);
		FORMID actorFormid = converter.findRecordFormidByEDID("tes4" + actorName);

		if (actorFormid == NULL) {
			log_error << "Couldn't find FORMID for the actor tes4" << actorName << "\n";
			continue;
		}

		newAchr->NAME.value = actorFormid;
		GENPOSDATA *achrPos = new GENPOSDATA();
		achrPos->posX = 0;
		achrPos->posY = 0;
		achrPos->posZ = 0;
		achrPos->rotX = 0;
		achrPos->rotY = 0;
		achrPos->rotZ = 0;
		newAchr->DATA.value = achrPos;
		newCell->ACHR.push_back(newAchr);

		converter.insertToEdidMap(achrEdid, newAchr->formID);
	}

	skyrimMod->CELL.cell_pool.construct(newCell, NULL, false);

	std::transform(cellEdid.begin(), cellEdid.end(), cellEdid.begin(), ::tolower);

	converter.insertToEdidMap(cellEdid, newCell->formID);
}

int main(int argc, char * argv[]) {

	char* input = "Input.esm";
	char* output = "Output.esp";
	char* inputModName = "myMod";

	if (argc < 4) {
		std::cout << "usage: GECKFrontend.exe <input folder> <output folder> <scripts folder>";
		return 0;
	}

	logger.init(argc, argv);

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

	addSpeakAsNpcs(converter, skyrimCollection);

	log_debug << std::endl << "Converting DIAL records.. " << std::endl;
	std::vector<Sk::DIALRecord *> *resDIAL = converter.convertDIALFromOblivion();

	/**
	* @todo - How we handle topics splitted into N dialogue topics and suffixed by QSTI value?
	*/
	for (uint32_t it = 0; it < resDIAL->size(); ++it) {
		Sk::DIALRecord *dial = (Sk::DIALRecord*)(*resDIAL)[it];
		std::string dialEdid = std::string(dial->EDID.value);
		std::transform(dialEdid.begin(), dialEdid.end(), dialEdid.begin(), ::tolower);
		converter.insertToEdidMap(dialEdid, dial->formID);
	}

	log_debug << std::endl << "Converting QUST records.. " << std::endl;
	std::vector<Sk::QUSTRecord *> *resQUST = converter.convertQUSTFromOblivion();

	log_debug << std::endl << "Converting PACK records.. " << std::endl;
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
			log_warning << e.what() << "\n";
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

	log_debug << std::endl << "Binding VMADs to ACTI records.. " << std::endl;
	convertACTI(converter);
	log_debug << std::endl << "Binding VMADs to CONT records.. " << std::endl;
	convertCONT(converter);
	log_debug << std::endl << "Binding VMADs to DOOR records.. " << std::endl;
	convertDOOR(converter);
	log_debug << std::endl << "Binding VMADs to NPC_ records.. " << std::endl;
	convertNPC_(converter);
	log_debug << std::endl << "Binding VMADs to WEAP records.. " << std::endl;
	convertWEAP(converter);
	log_debug << std::endl << "Binding VMADs to ARMO records.. " << std::endl;
	convertARMO(converter);
	log_debug << std::endl << "Binding VMADs to BOOK records.. " << std::endl;
	convertBOOK(converter);
	log_debug << std::endl << "Binding VMADs to INGR records.. " << std::endl;
	convertINGR(converter);
	log_debug << std::endl << "Binding VMADs to KEYM records.. " << std::endl;
	convertKEYM(converter);
	log_debug << std::endl << "Binding VMADs to MISC records.. " << std::endl;
	convertMISC(converter);
	log_debug << std::endl << "Binding VMADs to FLOR records.. " << std::endl;
	convertFLOR(converter);
	log_debug << std::endl << "Binding VMADs to FURN records.. " << std::endl;
	convertFURN(converter);
	log_debug << std::endl << "Binding VMADs to LIGH records.. " << std::endl;
	convertLIGH(converter);

    SaveFlags skSaveFlags = SaveFlags(2);

    skyrimCollection.SaveMod((ModFile*&)skyrimMod, skSaveFlags, "GECK.esp");

    return 0;

}

