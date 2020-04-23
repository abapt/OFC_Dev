#include "Reactor.hxx"
#include "EnrichmentPlant.hxx"
#include "Scenario.hxx"
#include "Storage.hxx"

#include <cmath>
#include <iostream>

////////////////////////////////////////////////////////////////
///////// Constructeur /////////////////////////////////////////
////////////////////////////////////////////////////////////////
Reactor::Reactor(double StartingTime, double LifeTime, double power, double MassHN,double BurnUp, 
				double LoadFactor):
{
  (*this).SetName("Reactor");

  fStorage = 0;
  fFabricationPlant = 0;
  fLoadFactor = LoadFactor;
  fPower = power * fLoadFactor;
  fMassHN = MassHN;
  fBurnUp = BurnUp;
  fCycleTime = (fBurnUp * 1e9 / (fPower)*fMassHN * 3600 * 24);

  // fScheduleHMMassEvolution.insert(vector<double>(fStartingTime, fMassHN));
}

////////////////////////////////////////////////////////////////
///////// Destructeur //////////////////////////////////////////
////////////////////////////////////////////////////////////////
Reactor::~Reactor() {}

////////////////////////////////////////////////////////////////
///////// Fonctions ////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void Reactor::CalculateU5Enrichment(double fBurnUp)
{
	fMassHN = 0.0135139 + 0.000563569*fBurnUp + 1.34642e-06*fBurnUp; // fBurnUp en GWj/t
}



	Evolution(T0){

	N(t) = N(T0) * exp(- sigma phi t);

	=> Modifier fMassU5Evolution et fMassU8Evolution
