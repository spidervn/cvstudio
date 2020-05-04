#include "CVTKTest.h"
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkChartXY.h>
#include <vtkTable.h>
#include <vtkPlot.h>
#include <vtkFloatArray.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkPen.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "app/interface/cv/ICVCore.h"
 
using namespace cv;

CVTKTest::CVTKTest()
{}

CVTKTest::~CVTKTest()
{}

int CVTKTest::run(int argc, char const* argv[])
{
    return run2();
    return run1();

    vtkSmartPointer<vtkTable> table = vtkSmartPointer<vtkTable>::New();
    vtkSmartPointer<vtkFloatArray> arrX = vtkSmartPointer<vtkFloatArray>::New();     
    
    arrX->SetName("X Axis");
    table->AddColumn(arrX);

    vtkSmartPointer<vtkFloatArray> arrC = 
    vtkSmartPointer<vtkFloatArray>::New();
    arrC->SetName("Cosine");
    table->AddColumn(arrC);

    vtkSmartPointer<vtkFloatArray> arrS = vtkSmartPointer<vtkFloatArray>::New();
    arrS->SetName("Sine");
    table->AddColumn(arrS);

    // Fill in the table with some example values
    int numPoints = 69;
    float inc = 7.5 / (numPoints-1);
    table->SetNumberOfRows(numPoints);
    for (int i = 0; i < numPoints; ++i)
    {
        table->SetValue(i, 0, i * inc);
        table->SetValue(i, 1, cos(i * inc));
        table->SetValue(i, 2, sin(i * inc));
    }

    // Set up the view
    vtkSmartPointer<vtkContextView> view = vtkSmartPointer<vtkContextView>::New();
    view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);

    // Add multiple line plots, setting the colors etc
    vtkSmartPointer<vtkChartXY> chart = vtkSmartPointer<vtkChartXY>::New();
    view->GetScene()->AddItem(chart);

    vtkPlot *line = chart->AddPlot(vtkChart::LINE);
    line->SetInputData(table, 0, 1);
    line->SetColor(0, 255, 0, 255);
    line->SetWidth(1.0);
    line = chart->AddPlot(vtkChart::LINE);
    line->SetInputData(table, 0, 2);
    line->SetColor(255, 0, 0, 255);
    line->SetWidth(5.0);

    // For dotted line, the line type can be from 2 to 5 for different dash/dot
    // patterns (see enum in vtkPen containing DASH_LINE, value 2):
    #ifndef WIN32
    line->GetPen()->SetLineType(vtkPen::DASH_LINE);
    #endif
    // (ifdef-ed out on Windows because DASH_LINE does not work on Windows
    //  machines with built-in Intel HD graphics card...)

    //view->GetRenderWindow()->SetMultiSamples(0);

    // Start interactor
    view->GetRenderWindow()->Render();
    view->GetInteractor()->Initialize();
    view->GetInteractor()->Start();

    return EXIT_SUCCESS;
}


int CVTKTest::run1()
{
    vtkSmartPointer<vtkTable> table; 
    vtkSmartPointer<vtkFloatArray> arrX; 
    vtkSmartPointer<vtkFloatArray> arrC; 
    vtkSmartPointer<vtkFloatArray> arrS;

    table = vtkSmartPointer<vtkTable>::New();
    arrX = vtkSmartPointer<vtkFloatArray>::New();
    arrC = vtkSmartPointer<vtkFloatArray>::New();
    arrS = vtkSmartPointer<vtkFloatArray>::New();

    arrX->SetName("X Axis");
    arrC->SetName("Cosine");
    arrS->SetName("Sine");

    table->AddColumn(arrX);
    table->AddColumn(arrC);
    table->AddColumn(arrS);

    // Fill in the table with some example values
    int numPoints = 69;
    float inc = 7.5 / (numPoints-1);
    table->SetNumberOfRows(numPoints);
    for (int i = 0; i < numPoints; ++i)
    {
        table->SetValue(i, 0, i * inc);
        table->SetValue(i, 1, cos(i * inc));
        table->SetValue(i, 2, sin(i * inc));
    }

    // Set up the view
    vtkSmartPointer<vtkContextView> view;
    vtkSmartPointer<vtkChartXY> chart;
    
    view = vtkSmartPointer<vtkContextView>::New();
    view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);

    // Add multiple line plots, setting the colors etc
    chart = vtkSmartPointer<vtkChartXY>::New();
    view->GetScene()->AddItem(chart);

    vtkPlot *line = chart->AddPlot(vtkChart::LINE);
    line->SetInputData(table, 0, 1);
    line->SetColor(0, 255, 0, 255);
    line->SetWidth(1.0);
    line = chart->AddPlot(vtkChart::LINE);
    line->SetInputData(table, 0, 2);
    line->SetColor(255, 0, 0, 255);
    line->SetWidth(5.0);


    // For dotted line, the line type can be from 2 to 5 for different dash/dot
    // patterns (see enum in vtkPen containing DASH_LINE, value 2):
    #ifndef WIN32
    // line->GetPen()->SetLineType(vtkPen::DASH_LINE);
    #endif
    // (ifdef-ed out on Windows because DASH_LINE does not work on Windows
    //  machines with built-in Intel HD graphics card...)

    //view->GetRenderWindow()->SetMultiSamples(0);

    // Start interactor
    view->GetRenderWindow()->Render();
    view->GetInteractor()->Initialize();
    view->GetInteractor()->Start();
    return 0;
}

int CVTKTest::run2()
{
    double x0 = 100;
    double y0 = 100;

    double arrx[] = { 100, 120, 70};
    double arry[] = { 85, 76, 170};

    double theta = 0.0;
    double numPoints = 100;
    double step_theta = 2 * CV_PI / numPoints;    

    int n = ARRAYSIZE(arrx);

    {
        vtkSmartPointer<vtkTable> table; 
        vtkSmartPointer<vtkFloatArray> arrX; 
        vtkSmartPointer<vtkFloatArray> arrC;
        vtkSmartPointer<vtkFloatArray> arrS;

        table = vtkSmartPointer<vtkTable>::New();
        arrX = vtkSmartPointer<vtkFloatArray>::New();
        arrC = vtkSmartPointer<vtkFloatArray>::New();
        arrS = vtkSmartPointer<vtkFloatArray>::New();

        arrX->SetName("Theta");
        //arrC->SetName("R");
        //arrS->SetName("Sine");
        table->AddColumn(arrX);

        for (int i=0; i<n; ++i)
        {
            char szBuff[100];
            sprintf(szBuff, "R_%02d", i);           

            vtkSmartPointer<vtkFloatArray> arrVal;
            arrVal = vtkSmartPointer<vtkFloatArray>::New();
            arrVal->SetName(szBuff);
            table->AddColumn(arrVal);

        }
        //table->AddColumn(arrC);
        //table->AddColumn(arrS);

        int i = 0;
        table->SetNumberOfRows((int)numPoints);
        for (;theta < 2 * CV_PI; theta += step_theta)
        {
            table->SetValue(i, 0, theta);

            for (int j=0; j<n; ++j)
            {
                double r = arrx[j] * cos(theta) + arry[j] * sin(theta);
                table->SetValue(i, 1+j, r);
            }
            i++;
        }

        // Set up the view
        vtkSmartPointer<vtkContextView> view;
        vtkSmartPointer<vtkChartXY> chart;
        
        view = vtkSmartPointer<vtkContextView>::New();
        view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);

        // Add multiple line plots, setting the colors etc
        chart = vtkSmartPointer<vtkChartXY>::New();
        view->GetScene()->AddItem(chart);

        for (int j=0; j<n; ++j)
        {
            vtkPlot *line = chart->AddPlot(vtkChart::LINE);
            line->SetInputData(table, 0, 1+j);
            line->SetColor(0, 255, 0, 255);
            line->SetWidth(1.0);
        }
        
        view->GetRenderWindow()->Render();
        view->GetInteractor()->Initialize();
        view->GetInteractor()->Start();
    }

    return 0;
}