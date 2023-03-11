// Fill out your copyright notice in the Description page of Project Settings.


#include "ISavableObject.h"


FSaveDataRecord ISavableObject::GetFSaveDataRecord_Implementation()
{
	return {};
}

// Add default functionality here for any IISavableObject functions that are not pure virtual.
void ISavableObject::LoadFromFSaveDataRecord_Implementation(FSaveDataRecord Record)
{
}
