#include "CProbabilityApp.h"
#include <vector>
#include "app/impl/general/CConsole.h"
#include "app/impl/background/probability/CProbabilityUtil.h"

using namespace std;

CProbabilityApp::CProbabilityApp(/* args */)
{
}

CProbabilityApp::~CProbabilityApp()
{
}

int CProbabilityApp::run(int argc, char const *argv[])
{
    vector<double> vPrior({ 1.0/5.0, 1.0/5.0, 1.0/5.0, 1.0/5.0, 1.0/5.0 });
    vector<double> vLikelihood({ 1.0/4.0, 1.0/6.0, 1.0/8.0, 1.0/12.0, 1.0/20.0 });
    vector<double> vPost;
    int n = vPrior.size();

    IProbabilityUtilPtr pup = CProbabilityUtilPtrNew;
    pup->bayesUpdateTable(n, vPrior, vLikelihood, vPost);

    printf("Posterior\r\n");
    CConsole::print(vPrior);
    CConsole::print(vPost);

    return 0;
}

