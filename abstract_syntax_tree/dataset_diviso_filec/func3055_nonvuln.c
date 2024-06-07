void Dispatcher::initBegin(Device & d) {
	
	for (auto i = 0; i < 20; ++i) {
		d.m_memData1[i] = m_mode.data1[i];
		d.m_memData2[i] = m_mode.data2[i];
	}

	
	d.m_memPrecomp.write(true);
	d.m_memData1.write(true);
	d.m_memData2.write(true);

	
	d.m_memPrecomp.setKernelArg(d.m_kernelInit, 0);
	d.m_memPointsDeltaX.setKernelArg(d.m_kernelInit, 1);
	d.m_memPrevLambda.setKernelArg(d.m_kernelInit, 2);
	d.m_memResult.setKernelArg(d.m_kernelInit, 3);
	CLMemory<cl_ulong4>::setKernelArg(d.m_kernelInit, 4, d.m_clSeed);

	
	d.m_memPointsDeltaX.setKernelArg(d.m_kernelInverse, 0);
	d.m_memInversedNegativeDoubleGy.setKernelArg(d.m_kernelInverse, 1);

	
	d.m_memPointsDeltaX.setKernelArg(d.m_kernelIterate, 0);
	d.m_memInversedNegativeDoubleGy.setKernelArg(d.m_kernelIterate, 1);
	d.m_memPrevLambda.setKernelArg(d.m_kernelIterate, 2);

	
	if(d.m_kernelTransform) {
		d.m_memInversedNegativeDoubleGy.setKernelArg(d.m_kernelTransform, 0);
	}

	
	d.m_memInversedNegativeDoubleGy.setKernelArg(d.m_kernelScore, 0);
	d.m_memResult.setKernelArg(d.m_kernelScore, 1);
	d.m_memData1.setKernelArg(d.m_kernelScore, 2);
	d.m_memData2.setKernelArg(d.m_kernelScore, 3);

	CLMemory<cl_uchar>::setKernelArg(d.m_kernelScore, 4, d.m_clScoreMax); 

	
	initContinue(d);
}