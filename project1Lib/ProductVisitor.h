/**
 * @file ProductVisitor.h
 * @author zhi lin
 *
 *
 */

#include "ItemVisitor.h"
#include "Product.h"

#ifndef PRODUCTVISITOR_H
#define PRODUCTVISITOR_H

class ProductVisitor : public ItemVisitor
{
private:
    std::vector<Product*> mProducts;

public:
    virtual ~ProductVisitor()
    {
    }

    void VisitProduct(Product* product) override
    {
        mProducts.push_back(product);
    }

    std::vector<Product*> GetProducts() const { return mProducts; }
};

#endif //PRODUCTVISITOR_H
