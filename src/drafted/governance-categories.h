
/*
	CATEGORY MAPPING

	* means the category has an associated class
	
	CAnodosNetwork: ANDS NETWORK (ROOT)
	has:
		vector<CNetworkVariable> vecNetworkVariables;
		vector<CAnodosProject> vecProjects;
		vector<CGovernanceObject> vecProposals;
		vector<CBudgetContract> vecContracts;
		vector<CBudgetUsers> vecUsers;

	CAnodosProject:
	has:
		name
		employees

*/

	// ANDS NETWORK (ROOT)
	// 	-> NETWORK VARIABLE
	// 		-> switch, setting
	// 	-> CATEGORIES
	// 		-> LEVEL
	// 			-> I, II, III, IV, V, VI, VII, VIII, IX, X, XI
	// 		-> VALUEOVERRIDE
	// 			-> NETWORK, OWNER 
	// 		-> PROJECT*
	// 			-> TYPES
	// 				-> SOFTWARE
	// 					-> CORE, NONCORE
	// 				-> HARDWARE
	// 				-> PR
	// 			-> PROJECT REPORT*
	// 				-> UPDATE
	// 			-> PROJECT MILEANDS*
	// 				-> START, ONGOING, COMPLETE, FAILURE
	// 			-> PROPOSAL*
	// 				-> FUNDING, GOVERNANCE, AMEND, GENERIC
	// 			-> CONTRACT*
	// 				-> TYPE
	// 					-> INTERNAL, EXTERNAL
	// 				-> STATUS
	// 					-> OK
	// 	-> GROUPS
	// 		-> GROUP1
	// 			-> USER1 (only users are allowed here in this scope)
	// 			-> USER2
	// 		-> GROUP2 (EVO)
	// 			-> VALUEOVERRIDE (STORE=ANDSDRIVE)
	// 			-> USER1

	// 	-> COMPANIES
	// 		-> COMPANY1
	// 		-> DAO1

