/*
Copyright: LaBRI (http://www.labri.fr)

Author(s): Florent Berthaut
Last modification: 2013

Adviser(s): Myriam Desainte-Catherine (myriam.desainte-catherine@labri.fr)

This software is a computer program whose purpose is to propose
a library for interactive scores edition and execution.

This software is governed by the CeCILL-C license under French law and
abiding by the rules of distribution of free software.  You can  use,
modify and/ or redistribute the software under the terms of the CeCILL-C
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-C license and that you accept its terms.
*/

/*!
 * \file CEngines.cpp
 * \author Florent Berthaut
 * \date 2013
 */

#include "Includes/Engines.h"

using namespace std;

#ifdef __cplusplus
extern "C"
{
#endif

Engines* createEngines(unsigned int maxSceneWitdth, std::string plugginsLocation)
{
    Engines* newEngines = new Engines(maxSceneWitdth, plugginsLocation);
    return newEngines;
}

Engines* createEnginesWithCallbacks(void(*crossAction)(unsigned int, unsigned int, std::vector<unsigned int>),
				 void(*triggerAction)(bool, unsigned int, unsigned int, unsigned int, std::string),
				 void(*isExecutionFinished)(),
				 unsigned int maxSceneWitdth,
				 std::string plugginsLocation)
{
	Engines* newEngines= new Engines(crossAction, triggerAction, isExecutionFinished, maxSceneWitdth, plugginsLocation);

    return newEngines;
}

void deleteEngines(Engines* eng)
{
    delete eng;
}

ECOMachine* getExecutionMachine(Engines* eng)
{
	return eng->getExecutionMachine();
}

Editor* getEditor(Engines* eng)
{
	return eng->getEditor();
}

void reset(Engines* eng, unsigned int maxSceneWidth)
{
    eng->reset(maxSceneWidth);
}

void resetWithCallbacks(Engines* eng, void(*crossAction)(unsigned int, unsigned int, std::vector<unsigned int>),
					void(*triggerAction)(bool, unsigned int, unsigned int, unsigned int, std::string),
					unsigned int maxSceneWidth)
{

    eng->reset(crossAction, triggerAction, maxSceneWidth);
}

void addCrossingCtrlPointCallback(Engines* eng, void(*pt2Func)(unsigned int, unsigned int, std::vector<unsigned int>))
{
	eng->addCrossingCtrlPointCallback(pt2Func);
}

void removeCrossingCtrlPointCallback(Engines* eng)
{
    eng->removeCrossingCtrlPointCallback();
}

void addCrossingTrgPointCallback(Engines* eng, void(*pt2Func)(bool, unsigned int, unsigned int, unsigned int, std::string))
{
    eng->addCrossingTrgPointCallback(pt2Func);
}

void removeCrossingTrgPointCallback(Engines* eng)
{
    eng->removeCrossingTrgPointCallback();
}

void addExecutionFinishedCallback(Engines* eng, void(*pt2Func)())
{
    eng->addExecutionFinishedCallback(pt2Func);
}

void removeExecutionFinishedCallback(Engines* eng)
{
    eng->removeExecutionFinishedCallback();
}

void addEnginesNetworkUpdateCallback(Engines* eng, void(*pt2Func)(unsigned int, std::string, std::string))
{
    eng->addEnginesNetworkUpdateCallback(pt2Func);
}

void removeEnginesNetworkUpdateCallback(Engines* eng)
{
    eng->removeEnginesNetworkUpdateCallback();
}




// Edition ////////////////////////////////////////////////////////////////////////

unsigned int addBox(Engines* eng, int boxBeginPos, int boxLength, unsigned int motherId)
{
    return eng->addBox(boxBeginPos, boxLength, motherId);
}

unsigned int addBoxWithBounds(Engines* eng, int boxBeginPos, int boxLength, unsigned int motherId, int minBound, int maxBound)
{
    return eng->addBox(boxBeginPos, boxLength, motherId, minBound, maxBound);
}

void changeBoxBounds(Engines* eng, unsigned int boxId, int minBound, int maxBound)
{
    eng->changeBoxBounds(boxId, minBound, maxBound);
}

void removeBox(Engines* eng, unsigned int boxId)
{
    eng->removeBox(boxId);
}

void setBoxOptionalArgument(Engines* eng, unsigned int boxId, std::string key, std::string value)
{
    eng->setBoxOptionalArgument(boxId, key, value);
}

void removeBoxOptionalArgument(Engines* eng, unsigned int boxId, std::string key)
{
    eng->removeBoxOptionalArgument(boxId, key);
}

std::map<std::string, std::string> getBoxOptionalArguments(Engines* eng, unsigned int boxId)
{
    return eng->getBoxOptionalArguments(boxId);
}

unsigned int addTemporalRelationWithBounds(Engines* eng, unsigned int boxId1,
										  unsigned int controlPoint1,
										  unsigned int boxId2,
										  unsigned int controlPoint2,
										  TemporalRelationType type,
										  int minBound,
										  int maxBound,
										  std::vector<unsigned int>& movedBoxes)
{
    return eng->addTemporalRelation(boxId1, controlPoint1, boxId2, controlPoint2, type, minBound, maxBound, movedBoxes);
}

unsigned int addTemporalRelation(Engines* eng, unsigned int boxId1,
										  unsigned int controlPoint1,
										  unsigned int boxId2,
										  unsigned int controlPoint2,
										  TemporalRelationType type,
										  std::vector<unsigned int>& movedBoxes)
{
    return eng->addTemporalRelation(boxId1, controlPoint1, boxId2, controlPoint2, type, movedBoxes);
}

void changeTemporalRelationBounds(Engines* eng, unsigned int relationId, int minBound, int maxBound, vector<unsigned int>& movedBoxes)
{
    eng->changeTemporalRelationBounds(relationId, minBound, maxBound, movedBoxes);
}

bool isTemporalRelationExisting(Engines* eng, unsigned int boxId1, unsigned int controlPoint1Index, unsigned int boxId2, unsigned int controlPoint2Index)
{
    return eng->isTemporalRelationExisting(boxId1, controlPoint1Index, boxId2, controlPoint2Index);
}



void removeTemporalRelation(Engines* eng, unsigned int relationId)
{
	eng->removeTemporalRelation(relationId);
}

unsigned int getRelationFirstBoxId(Engines* eng, unsigned int relationId)
{
    return eng->getRelationFirstBoxId(relationId);
}

unsigned int getRelationFirstCtrlPointIndex(Engines* eng, unsigned int relationId)
{
    return eng->getRelationFirstCtrlPointIndex(relationId);
}

unsigned int getRelationSecondBoxId(Engines* eng, unsigned int relationId)
{
    return eng->getRelationSecondBoxId(relationId);
}

unsigned int getRelationSecondCtrlPointIndex(Engines* eng, unsigned int relationId)
{
    return eng->getRelationSecondCtrlPointIndex(relationId);
}

int getRelationMinBound(Engines* eng, unsigned int relationId)
{
    return eng->getRelationMinBound(relationId);
}

int getRelationMaxBound(Engines* eng, unsigned int relationId)
{
    return eng->getRelationMaxBound(relationId);
}

bool performBoxEditing(Engines* eng, unsigned int boxId, int x, int y, vector<unsigned int>& movedBoxes, unsigned int maxModification)
{
    return eng->performBoxEditing(boxId, x, y, movedBoxes, maxModification);
}

int getBoxBeginTime(Engines* eng, unsigned int boxId)
{
    return eng->getBoxBeginTime(boxId);
}

int getBoxEndTime(Engines* eng, unsigned int boxId)
{
    return eng->getBoxEndTime(boxId);
}

int getBoxDuration(Engines* eng, unsigned int boxId)
{
    return eng->getBoxDuration(boxId);
}

int getBoxNbCtrlPoints(Engines* eng, unsigned int boxId)
{
    return eng->getBoxNbCtrlPoints(boxId);
}

int getBoxFirstCtrlPointIndex(Engines* eng, unsigned int boxId)
{
    return eng->getBoxFirstCtrlPointIndex(boxId);
}

int getBoxLastCtrlPointIndex(Engines* eng, unsigned int boxId)
{
    return eng->getBoxLastCtrlPointIndex(boxId);
}

void setCtrlPointMessagesToSend(Engines* eng, unsigned int boxId, unsigned int controlPointIndex, std::vector<std::string> messageToSend, bool muteState)
{
    eng->setCtrlPointMessagesToSend(boxId, controlPointIndex, messageToSend, muteState);
}

void getCtrlPointMessagesToSend(Engines* eng, unsigned int boxId, unsigned int controlPointIndex, std::vector<std::string>& messages)
{
    eng->getCtrlPointMessagesToSend(boxId, controlPointIndex, messages);
}

void removeCtrlPointMessagesToSend(Engines* eng, unsigned int boxId, unsigned int controlPointIndex)
{
    eng->removeCtrlPointMessagesToSend(boxId, controlPointIndex);
}

void setCtrlPointMutingState(Engines* eng, unsigned int boxId, unsigned int controlPointIndex, bool mute)
{
    eng->setCtrlPointMutingState(boxId, controlPointIndex, mute);
}

bool getCtrlPointMutingState(Engines* eng, unsigned int boxId, unsigned int controlPointIndex)
{
    return eng->getCtrlPointMutingState(boxId, controlPointIndex);
}

void setProcessMutingState(Engines* eng, unsigned int boxId, bool mute)
{
    eng->setProcessMutingState(boxId, mute);
}

bool getProcessMutingState(Engines* eng, unsigned int boxId)
{
    return eng->getProcessMutingState(boxId);
}

void setBoxMutingState(Engines* eng, unsigned int boxId, bool mute)
{
    eng->setBoxMutingState(boxId, mute);
}


//CURVES ////////////////////////////////////////////////////////////////////////////////////

void addCurve(Engines* eng, unsigned int boxId, const std::string & address)
{
    eng->addCurve(boxId, address);
}

void removeCurve(Engines* eng, unsigned int boxId, const std::string & address)
{
    eng->removeCurve(boxId, address);
}

void clearCurves(Engines* eng, unsigned int boxId)
{
    eng->clearCurves(boxId);
}

std::vector<std::string> getCurvesAddress(Engines* eng, unsigned int boxId)
{
    return eng->getCurvesAddress(boxId);
}

void setCurveSampleRate(Engines* eng, unsigned int boxId, const std::string & address, unsigned int nbSamplesBySec)
{
    eng->setCurveSampleRate(boxId, address, nbSamplesBySec);
}

unsigned int getCurveSampleRate(Engines* eng, unsigned int boxId, const std::string & address)
{
    return eng->getCurveSampleRate(boxId, address);
}

void setCurveRedundancy(Engines* eng, unsigned int boxId, const std::string & address, bool redondancy)
{
    eng->setCurveRedundancy(boxId, address, redondancy);
}

bool getCurveRedundancy(Engines* eng, unsigned int boxId, const std::string & address)
{
    return eng->getCurveRedundancy(boxId, address);
}

void setCurveMuteState(Engines* eng, unsigned int boxId, const std::string & address, bool muteState)
{
    eng->setCurveMuteState(boxId, address, muteState);
}

bool getCurveMuteState(Engines* eng, unsigned int boxId, const std::string & address)
{
    return eng->getCurveMuteState(boxId, address);
}

void getCurveArgTypes(Engines* eng, std::string stringToParse, std::vector<std::string>& result)
{
    eng->getCurveArgTypes(stringToParse, result);
}

bool setCurveSections(Engines* eng, unsigned int boxId, std::string address, unsigned int argNb,
						   const std::vector<float> & percent, const std::vector<float> & y, const std::vector<short> & sectionType, const std::vector<float> & coeff)
{
    return eng->setCurveSections(boxId, address, argNb, percent, y, sectionType, coeff);
}

bool getCurveSections(Engines* eng, unsigned int boxId, std::string address, unsigned int argNb,
		std::vector<float> & percent,  std::vector<float> & y,  std::vector<short> & sectionType,  std::vector<float> & coeff)
{
    return eng->getCurveSections(boxId, address, argNb, percent, y, sectionType, coeff);
}

bool getCurveValues(Engines* eng, unsigned int boxId, const std::string & address, unsigned int argNb, std::vector<float>& result)
{
    return eng->getCurveValues(boxId, address, argNb, result);
}





unsigned int addTriggerPoint(Engines* eng, unsigned int containingBoxId)
{
    return eng->addTriggerPoint(containingBoxId);
}

void removeTriggerPoint(Engines* eng, unsigned int triggerId)
{
    eng->removeTriggerPoint(triggerId);
}

bool assignCtrlPointToTriggerPoint(Engines* eng, unsigned int triggerId, unsigned int boxId, unsigned int controlPointIndex)
{
    return eng->assignCtrlPointToTriggerPoint(triggerId, boxId, controlPointIndex);
}

void freeTriggerPointFromCtrlPoint(Engines* eng, unsigned int triggerId)
{
    eng->freeTriggerPointFromCtrlPoint(triggerId);
}

void setTriggerPointMessage(Engines* eng, unsigned int triggerId, std::string triggerMessage)
{
    eng->setTriggerPointMessage(triggerId, triggerMessage);
}

std::string getTriggerPointMessage(Engines* eng, unsigned int triggerId)
{
    return eng->getTriggerPointMessage(triggerId);
}

unsigned int getTriggerPointRelatedBoxId(Engines* eng, unsigned int triggerId)
{
    return eng->getTriggerPointRelatedBoxId(triggerId);
}

unsigned int getTriggerPointRelatedCtrlPointIndex(Engines* eng, unsigned int triggerId)
{
    return eng->getTriggerPointRelatedCtrlPointIndex(triggerId);
}

void setTriggerPointMutingState(Engines* eng, unsigned int triggerId, bool muteState)
{
    eng->setTriggerPointMutingState(triggerId, muteState);
}

bool getTriggerPointMutingState(Engines* eng, unsigned int triggerId)
{
    return eng->getTriggerPointMutingState(triggerId);
}

void getBoxesId(Engines* eng, vector<unsigned int>& boxesID)
{
    eng->getBoxesId(boxesID);
}

void getRelationsId(Engines* eng, vector<unsigned int>& relationsID)
{
    eng->getRelationsId(relationsID);
}

void getTriggersPointId(Engines* eng, vector<unsigned int>& triggersID)
{
    eng->getTriggersPointId(triggersID);
}

//Execution ///////////////////////////////////////////////////////////
void setGotoValue(Engines* eng, unsigned int gotoValue)
{
    eng->setGotoValue(gotoValue);
}

unsigned int getGotoValue(Engines* eng)
{
    return eng->getGotoValue();
}

bool play(Engines* eng)
{
    return eng->play();
}

void pauseEngines(Engines* eng, bool pauseValue)
{
    eng->pause(pauseValue);
}

bool isPaused(Engines* eng)
{
    return eng->isPaused();
}

bool stop(Engines* eng)
{
    return eng->stop();
}

bool isRunning(Engines* eng)
{
    return eng->isRunning();
}

void compile(Engines* eng)
{
    eng->compile();
}

bool run(Engines* eng)
{
    return eng->run();
}

unsigned int getCurrentExecutionTime(Engines* eng)
{
    return eng->getCurrentExecutionTime();
}

void setExecutionSpeedFactor(Engines* eng, float factor)
{
    eng->setExecutionSpeedFactor(factor);
}

float getExecutionSpeedFactor(Engines* eng)
{
	return eng->getExecutionSpeedFactor();
}

float getProcessProgression(Engines* eng, unsigned int processId)
{
    return eng->getProcessProgression(processId);
}

void ignoreTriggerPointOnce(Engines* eng)
{
    eng->ignoreTriggerPointOnce();
}

void simulateNetworkMessageReception(Engines* eng, const std::string & netMessage)
{
    eng->simulateNetworkMessageReception(netMessage);
}

void getLoadedNetworkPlugins(Engines* eng, std::vector<std::string>& pluginsName, std::vector<unsigned int>& listeningPort)
{
    eng->getLoadedNetworkPlugins(pluginsName, listeningPort);
}

void addNetworkDevice(Engines* eng, const std::string & deviceName, const std::string & pluginToUse, const std::string & DeviceIp, const std::string & DevicePort)
{
    eng->addNetworkDevice(deviceName, pluginToUse, DeviceIp, DevicePort);
}

void removeNetworkDevice(Engines* eng, const std::string & deviceName)
{
	eng->removeNetworkDevice(deviceName);
}

void sendNetworkMessage(Engines* eng, const std::string & stringToSend)
{
	eng->sendNetworkMessage(stringToSend);
}

void getNetworkDevicesName(Engines* eng, std::vector<std::string>& devicesName, std::vector<bool>& couldSendNamespaceRequest)
{
    eng->getNetworkDevicesName(devicesName, couldSendNamespaceRequest);
}

std::vector<std::string> requestNetworkSnapShot(Engines* eng, const std::string & address)
{
    return eng->requestNetworkSnapShot(address);
}

int requestNetworkNamespace(Engines* eng, const std::string & address, vector<string>& nodes, vector<string>& leaves, vector<string>& attributs, vector<string>& attributsValue)
{
   return eng->requestNetworkNamespace(address, nodes, leaves, attributs, attributsValue); 
}



// LOAD AND STORE

void store(Engines* eng, std::string fileName)
{
    eng->store(fileName);
}

void load(Engines* eng, std::string fileName)
{
    eng->load(fileName);
}

void loadWithCallbacks(Engines* eng, std::string fileName,
				   void(*crossAction)(unsigned int, unsigned int, std::vector<unsigned int>),
				   void(*triggerAction)(bool, unsigned int, unsigned int, unsigned int, std::string))
{
    eng->load(fileName, crossAction, triggerAction);
}

void loadUsingAntoineFormat(Engines* eng, std::string fileName,
							void(*crossAction)(unsigned int, unsigned int, std::vector<unsigned int>),
							void(*triggerAction)(bool, unsigned int, unsigned int, unsigned int, std::string))
{
    eng->loadUsingAntoineFormat(fileName, crossAction, triggerAction);
}

// NETWORK

void print(Engines* eng) {
    eng->print();
}

void printExecutionInLinuxConsole(Engines* eng)
{
    eng->printExecutionInLinuxConsole();
}

#ifdef __cplusplus
}
#endif
