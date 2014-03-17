/*
 * XYData.hpp, part of LatAnalyze 3
 *
 * Copyright (C) 2013 - 2014 Antonin Portelli
 *
 * LatAnalyze 3 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LatAnalyze 3 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LatAnalyze 3.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef Latan_XYData_hpp_
#define Latan_XYData_hpp_

#include <LatAnalyze/Global.hpp>
#include <LatAnalyze/Chi2Function.hpp>
#include <LatAnalyze/FitInterface.hpp>
#include <LatAnalyze/Function.hpp>
#include <LatAnalyze/Mat.hpp>
#include <LatAnalyze/Minimizer.hpp>
#include <LatAnalyze/Model.hpp>
#include <vector>

BEGIN_NAMESPACE

/******************************************************************************
 *                           object for fit result                            *
 ******************************************************************************/
class FitResult: public DVec
{
    friend class XYStatData;
public:
    // constructors
    FitResult(void) = default;
    EIGEN_EXPR_CTOR(FitResult, FitResult, Base, MatExpr)
    // destructor
    virtual ~FitResult(void) = default;
    // access
    double                 getChi2(void) const;
    Index                  getNDof(void) const;
    double                 getChi2PerDof(void) const;
    const DoubleFunction & getModel(const Index j = 0) const;
private:
    double                      chi2_{0.0};
    Index                       nDof_{0};
    std::vector<DoubleFunction> model_;
};

/******************************************************************************
 *                    object for X vs. Y statistical data                     *
 ******************************************************************************/
class XYStatData: public FitInterface
{
public:
    enum
    {
        xx = 0,
        yy = 1,
        yx = 2
    };
public:
    // constructors
    XYStatData(void);
    XYStatData(const Index nData, const Index nXDim, const Index nYDim);
    // destructor
    virtual ~XYStatData(void) = default;
    // access
    void                 resize(const Index nData, const Index xDim,
                                const Index yDim);
    Block<DMatBase>      x(const PlaceHolder ph1 = _,
                           const PlaceHolder ph2 = _);
    ConstBlock<DMatBase> x(const PlaceHolder ph1 = _,
                           const PlaceHolder ph2 = _) const;
    Block<DMatBase>      x(const Index i, const PlaceHolder ph2 = _);
    ConstBlock<DMatBase> x(const Index i, const PlaceHolder ph2 = _) const;
    Block<DMatBase>      x(const PlaceHolder ph1, const Index k);
    ConstBlock<DMatBase> x(const PlaceHolder ph1, const Index k) const;
    double &             x(const Index i, const Index k);
    const double &       x(const Index i, const Index k) const;
    Block<DMatBase>      y(const PlaceHolder ph1 = _,
                           const PlaceHolder ph2 = _);
    ConstBlock<DMatBase> y(const PlaceHolder ph1 = _,
                           const PlaceHolder ph2 = _) const;
    Block<DMatBase>      y(const Index i, const PlaceHolder ph2 = _);
    ConstBlock<DMatBase> y(const Index i, const PlaceHolder ph2 = _) const;
    Block<DMatBase>      y(const PlaceHolder ph1, const Index k);
    ConstBlock<DMatBase> y(const PlaceHolder ph1, const Index k) const;
    double &             y(const Index i, const Index k);
    const double &       y(const Index i, const Index k) const;
    Block<DMatBase>      xxVar(const Index i1, const Index i2);
    ConstBlock<DMatBase> xxVar(const Index i1, const Index i2) const;
    Block<DMatBase>      yyVar(const Index j1, const Index j2);
    ConstBlock<DMatBase> yyVar(const Index j1, const Index j2) const;
    Block<DMatBase>      yxVar(const Index j,  const Index i);
    ConstBlock<DMatBase> yxVar(const Index j,  const Index i) const;
    // fit
    FitResult fit(const std::vector<const DoubleModel *> &modelVector,
                  Minimizer &minimizer, const DVec &init,
                  const bool reinitChi2 = true,
                  const FitVerbosity verbosity = FitVerbosity::Silent);
    FitResult fit(const DoubleModel &model, Minimizer &minimizer,
                  const DVec &init, const bool reinitChi2 = true,
                  const FitVerbosity verbosity = FitVerbosity::Silent);
                  
private:
    DMat         x_, y_;
    Mat<DMat>    var_[3];
    IVec         isXExact_, isFitPoint_;
    Chi2Function chi2_;
};

END_NAMESPACE

#endif // Latan_XYData_hpp_
