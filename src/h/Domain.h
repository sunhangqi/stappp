/*****************************************************************************/
/*  STAP++ : A C++ FEM code sharing the same input data file with STAP90     */
/*     Computational Dynamics Laboratory                                     */
/*     School of Aerospace Engineering, Tsinghua University                  */
/*                                                                           */
/*     Release 1.0, October 14, 2017                                         */
/*                                                                           */
/*     http://www.comdyn.cn/                                                 */
/*****************************************************************************/

#pragma once

#include <string>
#include <fstream>
#include <vector>

#include "Node.h"
#include "Bar.h"
#include "Outputter.h"
#include "Solver.h"
#include "LoadCaseData.h"
#include "SkylineMatrix.h"

using namespace std;

//!	Clear an array
template <class type> void clear( type* a, unsigned int N );

//!	Domain class : Define the problem domain
/*!	Only a single instance of Domain class can be created */
class CDomain
{
private:

//!	The instance of the Domain class
	static CDomain* _instance;

//!	Input file stream for reading data from input data file
	ifstream Input;

//!	Heading information for use in labeling the outpu
	char Title[256]; 

//!	Solution MODEX
/*!		0 : Data check only;
		1 : Execution */
	unsigned int MODEX;

//!	Total number of nodal points
	unsigned int NUMNP;

//!	List of all nodes in the domain
	CNode* NodeList;

//!	Total number of element groups.
/*! An element group consists of a convenient collection of elements with same type */
	unsigned int NUMEG;

//!	Element type of each group
	unsigned int* ElementTypes;

//!	Number of elements in each element group
	unsigned int* NUME;

//!	Element Set List
/*!		ElementSetList[i] - ith element set */
/*!		ElementSetList[i][j] - jth element in ith set */
	CElement** ElementSetList;

//!	Number of different sets of material/section properties in each element group
	unsigned int* NUMMAT;

//!	Material set list
/*!		MaterialSetList[i] - ith material set */
/*!		MaterialSetList[i][j] - jth material in ith set */
	CMaterial** MaterialSetList;

//!	Number of load cases
	unsigned int NLCASE;

//!	List of all load cases
	CLoadCaseData* LoadCases;

//!	Number of concentrated loads applied in each load case
	unsigned int* NLOAD;

//!	Total number of equations in the system
	unsigned int NEQ;

//!	Number of elements in banded global stiffness matrix
	unsigned int NWK;

//!	Maximum half bandwith
	unsigned int MK;

//!	Banded stiffness matrix
/*! A one-dimensional array storing only the elements below the	skyline of the 
    global stiffness matrix. */
    CSkylineMatrix<double>* StiffnessMatrix;

//!	Global nodal force/displacement vector
	double* Force;

public:

//!	Constructor
	CDomain();

//!	Desconstructor
	~CDomain();

//!	Return pointer to the instance of the Domain class
	static CDomain* Instance();

//!	Read domain data from the input data file
	bool ReadData(string FileName, string OutFile);

//!	Read nodal point data
	bool ReadNodalPoints();

//!	Read load case data
	bool ReadLoadCases();

//!	Read element data
	bool ReadElements();

//!	Read bar element data from the input data file
	bool ReadBarElementData(unsigned int EleGrp);

//!	Calculate global equation numbers corresponding to every degree of freedom of each node
	void CalculateEquationNumber();

//!	Calculate column heights
	void CalculateColumnHeights();

//!	Calculate address of diagonal elements in banded matrix
	void CalculateDiagnoalAddress();

//! Allocate storage for matrices
/*!	Allocate Force, ColumnHeights, DiagonalAddress and StiffnessMatrix and 
    calculate the column heights and address of diagonal elements */
	void AllocateMatrices();

//!	Assemble the banded gloabl stiffness matrix
	void AssembleStiffnessMatrix();

//!	Assemble the global nodal force vector for load case LoadCase
	bool AssembleForce(unsigned int LoadCase); 

//!	Return solution mode
	inline unsigned int GetMODEX() { return MODEX; }

//!	Return the title of problem
	inline string GetTitle() { return Title; }

//!	Return the total number of equations
	inline unsigned int GetNEQ() { return NEQ; }

//!	Return the total number of nodal points
	inline unsigned int GetNUMNP() { return NUMNP; }

//!	Return the number of banded global stiffness matrix elements
	inline unsigned int GetNWK() { return NWK; }

//!	Return the maximum half bandwith
	inline unsigned int GetMK() { return MK; }

//!	Return the node list
	inline CNode* GetNodeList() { return NodeList; }

//!	Return the number of elements in each element group
	inline unsigned int* GetNUME() { return NUME; }

//!	Return total number of element groups
	inline unsigned int GetNUMEG() { return NUMEG; }

//!	Element type of each group
	inline unsigned int* GetElementTypes() {return ElementTypes; }

//!	Return element Set List 
	inline CElement** GetElementSetList() { return ElementSetList; }

//!	Return number of different sets of material/section properties in each element group
	inline unsigned int* GetNUMMAT() { return NUMMAT; }

//!	Return material set list
	inline CMaterial** GetMaterialSetList() { return MaterialSetList; }

//!	Return pointer to the global nodal force vector
	inline double* GetForce() { return Force; }

//!	Return pointer to the global nodal displacement vector
	inline double* GetDisplacement() { return Force; }

//!	Return the total number of load cases
	inline unsigned int GetNLCASE() { return NLCASE; }

//!	Return the number of concentrated loads applied in each load case
	inline unsigned int* GetNLOAD() { return NLOAD; }

//!	Return the list of load cases
	inline CLoadCaseData* GetLoadCases() { return LoadCases; }

//!	Return pointer to the banded stiffness matrix
	inline CSkylineMatrix<double>* GetStiffnessMatrix() { return StiffnessMatrix; }

};
