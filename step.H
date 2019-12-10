//      Evaluate time step of Navier-Stokes equations

        //volScalarField muEff(turbulence->muEff())  ;
        //volScalarField k("k", thermo.Cp()*muEff/Pr);//thermal diffusivity
		//Info << "max(muEff)=" << max(muEff).value() << endl;
		//Info << "max(k)=" << max(k).value() << endl;

        //scalar CoNum = 0.0;
        scalar dtdx_inv= 0.0;
        scalar dtdx_rmu= 0.0;
        scalar dtdx_ral= 0.0;
		//scalar cmax = 0.0;
       

        //volScalarField lammax("lammax", zero*U.component(0));
        if (mesh.nInternalFaces())
        {
         surfaceScalarField cave
        (
            fvc::interpolate(c)
        );

		//Info << "cmax = " << max(cave).value() << endl; 
         surfaceScalarField un
        (
            fvc::interpolate(mag(U))
        );
         surfaceScalarField lambda("lambda", mag(un + cave));
         surfaceScalarField evmax("evmax", lambda);//
 

//dx is the distance between two centers projected along the face normal
         surfaceScalarField dx
         (
          1./mesh.surfaceInterpolation::deltaCoeffs()
         );

//       surfaceScalarField dx       = 1./mesh.surfaceInterpolation::nonOrthDeltaCoeffs();
//       surfaceScalarField dx2      = sqr(dx);
         surfaceScalarField dx2("dx2", sqr(dx));
//changed
         dtdx_inv= max(evmax/dx).value() ;//inviscid limitation
         //dtdx_rmu= max(evmu/dx2).value() ;//viscous limitation
         //dtdx_ral= max(eval/dx2).value() ;//viscous limitation
 
		//Info << "inviscid limitation is" << dtdx_inv << endl;
		//Info << "viscous limitation1 is" << dtdx_rmu << endl;
		//Info << "viscous limitation2 is" << dtdx_ral << endl;
         
         CoNum   = max(dtdx_inv,dtdx_rmu);
		 //Info << "CoNum=" << CoNum << endl;
         //CoNum   = max(dtdx_ral,CoNum)        ;
		 //Info << "CoNum2=" << CoNum << endl;
         CoNum   = 1./CoNum;
        }

        runTime.setDeltaT
        (
         maxCo*CoNum
        );

    
    	//Info << "CoNum3 = " << CoNum << endl;
		Info << "dt=" << maxCo*CoNum << endl;


