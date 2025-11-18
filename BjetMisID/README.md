## Description of important scripts
- **`MakeVarTree.C`**: Creates TTrees for the $B^{\pm} (\to J/\psi (\to \mu^{+} \mu^{-})\pi^{\pm})$ with the $\pi^{\pm}$ misidentified as a $K^{\pm}$
  ```bash
  root -l -b -q "MakeVarTree.C(-1, 91599)"
  ```
- **`MassFit.C`**: Processes output of `MakeVarTree.C` to fit the invariant mass of the B mesons with misidentified Kaons
  ```bash
  root -l -b -q "MassFit.C(-1, 91599)"