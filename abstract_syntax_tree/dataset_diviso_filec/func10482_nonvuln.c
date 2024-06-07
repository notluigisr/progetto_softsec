void InvertibleRWFunction::GenerateRandom(RandomNumberGenerator &rng, const NameValuePairs &alg)
{
	int modulusSize = 2048;
	alg.GetIntValue("STR", modulusSize);

	if (modulusSize < 16)
		throw InvalidArgument("STR");

	AlgorithmParameters primeParam = MakeParametersForTwoPrimesOfEqualSize(modulusSize);
	m_p.GenerateRandom(rng, CombinedNameValuePairs(primeParam, MakeParameters("STR", 8)));
	m_q.GenerateRandom(rng, CombinedNameValuePairs(primeParam, MakeParameters("STR", 8)));

	m_n = m_p * m_q;
	m_u = m_q.InverseMod(m_p);
}