#ifndef FASESINTAXIS_H_INCLUDED
#define FASESINTAXIS_H_INCLUDED

  void SintaxisEscribir(struct nodo *reco, int edo);
  void SintaxisLeer(struct nodo *reco, int edo);
  void SintaxisFor(struct nodo *reco, int edo);
  void SintaxisIf(struct nodo *reco, int edo);
  void SintaxisProgram(struct nodo *reco, int edo);
  void SintaxisVar(struct nodo *reco, int edo);
  void SintaxisConst(struct nodo *reco, int edo);

#endif // FASESINTAXIS_H_INCLUDED
