#include "EnrichmentPlant.hxx"
#include "Stock.hxx"
#include "Reactor.hxx"

#include <iostream>
#include <string>
using namespace std;

////////////////////////////////////////////////////////////////
///////// Constructeur /////////////////////////////////////////
////////////////////////////////////////////////////////////////
EnrichmentPlant::EnrichmentPlant(double WasteU5Content) {
  fU5ContentInUapp = 0.003;
  fU5ContentInUnat = 0.0072;
  fU5ContentInUenr = WasteU5Content;
  SetName("EnrichmentPlant.");
}

////////////////////////////////////////////////////////////////
///////// Destructeur //////////////////////////////////////////
////////////////////////////////////////////////////////////////
EnrichmentPlant::~EnrichmentPlant() {}

////////////////////////////////////////////////////////////////
///////// Fonctions ////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void EnrichmentPlant::CalculateRendement() {
  fRendement = (fU5ContentInUnat - fU5ContentInUapp) / (fU5ContentInUenr - fU5ContentInUapp);
}

fNeededUenrMassesByReactorLoading = Reactor->GetMassHN()
                                    fNeededUnatMassesByReactorLoading = fNeededUenrMassesByReactorLoading / Rendement
                                                                        fNeededUappMassesByReactorLoading = fNeededUnatMassesByReactorLoading -
                                                                            fNeededUenrMassesByReactorLoading
                                                                            
                                                                            
                                                                            