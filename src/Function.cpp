#include "HumbugEngine/Function.h"

Function::Function(std::shared_ptr<AnimationKey> key1, std::shared_ptr<AnimationKey> key2)
{
	// Set Keys
	if (key1->getTimeStamp() < key2->getTimeStamp()) {
		startKey = key1;
		endKey = key2;
	} else {
		startKey = key2;
		endKey = key1;
	}

	// Build Matrix
	float t1 = startKey->getValue(), t2 = endKey->getValue();
	std::array<float, 20> mat = {
		3 * pow(t1,2), 2 * t1, 1, 0, 0,
		3 * pow(t2,2), 2 * t2, 1, 0, 0,
		pow(t1,3), pow(t1,2), t1, 1, startKey->getTimeStamp(),
		pow(t2,3), pow(t2,2), t2, 1, endKey->getTimeStamp(),
	};

	// Compute Coeffs
	int limite = 4, j;
	float temp;
	for (int i = 0; i < limite; i++) {

		//Pivot
		j = i;
		bool pursue = true;
		while (pursue) {
			if (j < limite) {
				if (mat[j * 5 + i] == 0) { j++; }
				else { pursue = false; }
			}
			else { pursue = false; }
		}

		if (j != limite) {

			// Swap Rows
			for (int k = 0; k < 5; k++) {
				temp = mat[i * 5 + k];
				mat[i * 5 + k] = mat[j * 5 + k];
				mat[j * 5 + k] = temp;
			}

			//Reduction
			float val = mat[i * 5 + i];
			for (int x = 0; x < 5; x++) { mat[i * 5 + x] = mat[i * 5 + x] / val; }

			//Reiteration
			for (int y = 0; y < 4; y++) {
				if ((y != i) && mat[j * 5 + i] != 0) {
					float val2 = mat[y * 5 + i];
					for (int x = 0; x < 5; x++) { mat[y * 5 + x] -= val2 * mat[i * 5 + x]; }
				}
			}
		}
	}

	// Set Coeffs
	for (int ii = 0; ii < 4; ii++)
		m_coeffs[ii] = mat[ii * 5 + 4];
}

float Function::getValue(float time, bool smooth)
{
	if (time < startKey->getTimeStamp() || time > endKey->getTimeStamp()) return 0;
	if (smooth) return m_coeffs[0] * pow(time, 3) + m_coeffs[1] * pow(time, 2) + m_coeffs[2] * time + m_coeffs[3];
	else return startKey->getValue() + (endKey->getValue() - startKey->getValue())
		* (time - startKey->getTimeStamp()) / (endKey->getTimeStamp() - startKey->getTimeStamp());
}

std::shared_ptr<AnimationKey> Function::getStartKey() { return startKey; }
std::shared_ptr<AnimationKey> Function::getEndKey() { return endKey; }