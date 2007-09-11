#include "LSA.h"

bool OSPF::RouterLSA::Update (const OSPFRouterLSA* lsa)
{
    bool different = DiffersFrom (lsa);
    (*this) = (*lsa);
    ResetInstallTime ();
    if (different) {
        ClearNextHops ();
        return true;
    } else {
        return false;
    }
}

bool OSPF::RouterLSA::DiffersFrom (const OSPFRouterLSA* routerLSA) const
{
    const OSPFLSAHeader& lsaHeader = routerLSA->getHeader ();
    bool differentHeader = ((header_var.getLsOptions () != lsaHeader.getLsOptions ()) ||
                            ((header_var.getLsAge () == MAX_AGE) && (lsaHeader.getLsAge () != MAX_AGE)) ||
                            ((header_var.getLsAge () != MAX_AGE) && (lsaHeader.getLsAge () == MAX_AGE)) ||
                            (header_var.getLength () != lsaHeader.getLength ()));
    bool differentBody   = false;

    if (!differentHeader) {
        differentBody = ((V_VirtualLinkEndpoint_var != routerLSA->getV_VirtualLinkEndpoint ()) ||
                         (E_ASBoundaryRouter_var != routerLSA->getE_ASBoundaryRouter ()) ||
                         (B_AreaBorderRouter_var != routerLSA->getB_AreaBorderRouter ()) ||
                         (numberOfLinks_var != routerLSA->getNumberOfLinks ()) ||
                         (links_arraysize != routerLSA->getLinksArraySize ()));

        if (!differentBody) {
            unsigned int linkCount = links_arraysize;
            for (unsigned int i = 0; i < linkCount; i++) {
                bool differentLink = ((links_var[i].getLinkID () != routerLSA->getLinks (i).getLinkID ()) ||
                                      (links_var[i].getLinkData () != routerLSA->getLinks (i).getLinkData ()) ||
                                      (links_var[i].getType () != routerLSA->getLinks (i).getType ()) ||
                                      (links_var[i].getNumberOfTOS () != routerLSA->getLinks (i).getNumberOfTOS ()) ||
                                      (links_var[i].getLinkCost () != routerLSA->getLinks (i).getLinkCost ()) ||
                                      (links_var[i].getTosDataArraySize () != routerLSA->getLinks (i).getTosDataArraySize ()));

                if (!differentLink) {
                    unsigned int tosCount = links_var[i].getTosDataArraySize ();
                    for (unsigned int j = 0; j < tosCount; j++) {
                        bool differentTOS = ((links_var[i].getTosData (j).tos != routerLSA->getLinks (i).getTosData (j).tos) ||
                                             (links_var[i].getTosData (j).tosMetric[0] != routerLSA->getLinks (i).getTosData (j).tosMetric[0]) ||
                                             (links_var[i].getTosData (j).tosMetric[1] != routerLSA->getLinks (i).getTosData (j).tosMetric[1]) ||
                                             (links_var[i].getTosData (j).tosMetric[2] != routerLSA->getLinks (i).getTosData (j).tosMetric[2]));

                        if (differentTOS) {
                            differentLink = true;
                            break;
                        }
                    }
                }

                if (differentLink) {
                    differentBody = true;
                    break;
                }
            }
        }
    }

    return (differentHeader || differentBody);
}
