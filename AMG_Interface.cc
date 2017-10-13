#include "AMG_Interface.h" 
#include <memory>
AMG::AMG(gmm::csr_matrix<scalar_type> A_csr, std::vector<scalar_type> U, std::vector<scalar_type> B)
{
	std::cout<<"Start building the matrix"<<std::endl; 
	std::cout<<"*** parameters SAMG matrix   "<<A_csr.nrows()<<std::endl;	
		std::cout<<"*** parameters SAMG matrix   "<<A_csr.ncols()<<std::endl;
	APPL_INT nnu,nna;
	nnu=A_csr.nc; nna=A_csr.pr.size();
	double *a_samg;a_samg=new double[nna];
		double *u_samg;u_samg=new double[nnu];
		double *b_samg;b_samg=new double[nnu];
		APPL_INT *ja_samg;ja_samg=new APPL_INT[nna];
		APPL_INT *ia_samg;ia_samg=new APPL_INT[nnu+1];
		ia_samg[0]=1;
		unsigned int offset=0;
		for(int ia=0;ia<nnu+1-1;ia++){
			unsigned int nonzero=A_csr.jc.at(ia+1)-A_csr.jc.at(ia);
				ia_samg[ia+1] = nonzero + ia_samg[ia] ;
				u_samg[ia] = U[ia];
				b_samg[ia] = B[ia];
				// std::cout<<"Going from "<<offset<<" to "<<offset + nonzero<<std::endl;
				for (int innz=offset; innz<offset+nonzero; innz++ )
					if( ia == (int) A_csr.ir.at(innz))
					{	//WARNING: not working for a matrix with zero on the diagonal
						//	std::cout<<"diagonal term"<<std::endl; 
						if(fabs(A_csr.pr.at(innz))<1E-30)
							std::cout<<"****************************diagonal zero"<<std::endl;
								a_samg[offset]=A_csr.pr.at(innz);
								ja_samg[offset]=A_csr.ir.at(innz)+1;
								
					}
			int shift=1;
				for (int innz=offset; innz<offset+nonzero; innz++ )
					if( ia != (int) A_csr.ir.at(innz))
					{
						//	std::cout<<"non diagonal term "<< ia << " " << A_csr.ir.at(innz) <<std::endl; 
						if(fabs(A_csr.pr.at(innz))<1E-30)
							std::cout<<"****************************non diagonal zero "<<A_csr.pr.at(innz)<<std::endl;
								a_samg[offset+shift]=A_csr.pr.at(innz);
								ja_samg[offset+shift]=A_csr.ir.at(innz)+1;
								shift++;
					}
			//	std::cout<<std::endl;
			// std::cout<<"non zero in i "<<ia<<" are "<< nonzero<<std::endl; 
			offset+=nonzero;
		}













APPL_INT npnt,nsys,matrix;
				matrix=22; nsys=3;npnt=0;
				APPL_INT ndiu      = 1;        // dimension of (dummy) vector iu
				APPL_INT ncyc;

				float told,tnew,tamg;

				//SAMG configuration
				//i

				 APPL_INT * iu;
			if (nsys==1) iu= new APPL_INT[1];
			else {
 			iu  = new APPL_INT[nnu];
 			ndiu   = nnu;
			 for(int iiu=0;iiu<nnu;iiu++){
				//only working for nsys = 2 check it out for larger systems				 
				if(iiu < 882){
				 iu[iiu]=((iiu< 441)? 1:2);
				//iu[iiu]=1;
}
				else iu[iiu]=3;
				}//end for iiu
			}
				
			//=====================================================
			/// printing format
			char ch[] = "f";int len=1;
			SAMG_SET_IOFORM(&ch[0],&len);

			
			//==================================================			
			// int nrc	;
			// int nptmax; // max number of points for which we switch to nrc_emergency
			// int clsolver_finest;	// 
			// SAMG_GET_NRC(&nrc); // retreive nrc=solver for coarser levels page 67 user guide
			// std::cout<<"..value of nrc======"<<nrc<<std::endl;
			// ================================
			// 1  Iterative application of currently selected smoother 
			// 2  ILU(0) preconditioned CG 
			// 3  ILUT preconditioned BiCGstab 
			// 4  Diagonally preconditioned CG 
			// 5  Diagonally preconditioned BiCGstab 
			// 6  Dense direct solver (standard)  
			// 7  Sparse direct solver (standard)  
			// 8  Least squares solver (LSQ; robust but very expensive!) 
			// 9  Dummy interface routine (→ Section 8.3.1)  
			// 10  Dense direct solver (highly tuned, → cldense_ctrl below) 
			// 11  Sparse direct solver (Intel’s pardiso) if MKL has been linked 
			// 99  Another instance of SAMG 
			// ================================



			//==================================================	





//#ifdef DIRECT_SOLVER	
	
			int levelx;
			SAMG_GET_LEVELX(&levelx); // retreive levelx=number of maximum coarsening levels 
			 std::cout<<"..value of levelx======"<<levelx<<std::endl;
			levelx=1;
			SAMG_SET_LEVELX(&levelx);// change levelx=number of maximum coarsening levels 
			SAMG_GET_LEVELX(&levelx);// retreive levelx=number of maximum coarsening levels 
			std::cout<<"..check if change value of levelx======"<<levelx<<std::endl;
			
			int  nrc=4;int  nrc_emergency=4;int nptmax=5000;int clsolver_finest=1;
			  SAMG_SET_NRC(&nrc);// change  nrc=solver for coarser levels page 67 user guide
			SAMG_SET_NRC_EMERGENCY(&nrc_emergency);
			  SAMG_SET_NPTMAX(&nptmax);// change  nptmax
			  SAMG_SET_CLSOLVER_FINEST(&clsolver_finest);// change  nptmax
			// SAMG_GET_NRC(&nrc);// retreive  nrc=solver for coarser levels page 67 user guide
			// std::cout<<"..check if change value of nrc======"<<nrc<<std::endl;
			
			ncyc      = 11050;    // V-cycle as pre-conditioner for CG; at most 50 iterations

// #endif //direct_solver



#ifdef AMG_STAND_ALONE
			//Both ncgrad (the "nd number in ncyc) and ncgrad_default must be equal to 0 to use SAMG solver as a stand-alone solver (not as a preconditioner)
 				
			int ncgrad_default=0;
			SAMG_SET_NCGRAD_DEFAULT(&ncgrad_default);
			ncyc      = 10050;    // V-cycle as pre-conditioner for CG; at most 50 iterations
#endif //amg_stand_alone
			


#ifdef AMG_ACCELERATED

			ncyc      = 11050;    // V-cycle as pre-conditioner for CG; at most 50 iterations	
			
#endif //amg_accelerated

ncyc      = 11050;   

				APPL_INT ndip      = 1;        // dimension of (dummy) vector ip
				// APPL_INT * iscale = new APPL_INT[1];
				// this vector (iscale) indicates which uknowns require scaling if 0 no scaling
				APPL_INT * iscale = new APPL_INT[nsys]; for(int i_sys=0; i_sys<nsys; i_sys++) iscale[i_sys]=0; 
				APPL_INT * ip     = new APPL_INT[1];
				APPL_INT nsolve    = 2;        // results in scalar approach (current system is scalar)
				APPL_INT ifirst    = 1;        // first approximation = zero
				double  eps       = 1.0e-12;   // required (relative) residual reduction
				
				//ncyc      = 50050;
				APPL_INT n_default = 20;       // select default settings for secondary parameters

				// CURRENTLY AVAILABLE: 10-13, 15-18, 20-23, 25-28
				// NOTE: the higher the respective SECOND digit, the
				// more aggressive the coarsening (--> lower memory at
				// the expense of slower convergence)
				APPL_INT iswtch    = 5100+n_default; // complete SAMG run ....
				// ... memory de-allocation upon return ....
				// ... memory extension feature activated ....
				// ... residuals measured in the L2-norm .....
				// ... secondary parameter default setting # n_default

				// ===> Secondary parameters which have to be set if n_default=0
				//      (at the same time a demonstration of how to access secondary or hidden parameters)

				double a_cmplx   = 2.2;      // estimated dimensioning
				double g_cmplx   = 1.7;      // estimated dimensioning
				double w_avrge   = 2.4;      // estimated dimensioning
				double p_cmplx   = 0.0;      // estimated dimensioning (irrelevant for scalar case)
				double  chktol    = -1.0;    // input checking de-activated (we know it's ok!)
				
				//============================================
				//     idump controls the matrix dumping of SAMG				
				// 1  Standard print output, no matrix dump. 
				// 2‐6  Write matrices to disk: level 2 up to level idmp. 
				// 7  Write matrices to disk: level 2 up to the coarsest level. 
				// 8  Write finest‐level matrix to disk (incl. right hand side etc.). 
				// 9  Write all matrices to disk. 
				APPL_INT idump     = 9;       // minimum output during setup
				//============================================
				// iout page 44 Userguide. it controls display outpu. default 2 very verbose 43
				APPL_INT iout      = 2;        // display residuals per iteration and work statistics



				// output:
				APPL_INT ierr,ierrl,ncyc_done;
				double res_out,res_in;
				//end

				// for(int xx=0;xx<200;xx++)std::cout<<a_samg[xx]<<" "<<a[xx]<< " -- "<<ja_samg[xx]<<" "<<ja[xx] <<std::endl;
				SAMG_CTIME(&told);
				double time_SAMG=gmm::uclock_sec();
				std::cout<<"start solving with samg " << std::endl;



						SAMG(&nnu,&nna,&nsys,&ia_samg[0],&ja_samg[0],
						&a_samg[0],&b_samg[0],&u_samg[0],&iu[0],&ndiu,
						&ip[0],&ndip,&matrix,&iscale[0],
						&res_in,&res_out,&ncyc_done,&ierr,
						&nsolve,&ifirst,&eps,&ncyc,&iswtch,
						&a_cmplx,&g_cmplx,&p_cmplx,&w_avrge,
						&chktol,&idump,&iout);




std::cout << std::endl<<"*** time to solve the system using SAMG with gmm time: " << gmm::uclock_sec() - time_SAMG << " seconds\n";



gmm::resize(sol_vec,nnu);
for(int i = 0 ; i < nnu ; i++ ){sol_vec[i]=u_samg[i];}









}

