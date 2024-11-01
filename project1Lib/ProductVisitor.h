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

/**
 * visitor class for products
 * 
 */
class ProductVisitor : public ItemVisitor
{
private:
    std::vector<Product*> mProducts; ///< local storage for products

public:
    virtual ~ProductVisitor()
    {
    }

    /**
     * visit a product and store it in the local storage
     *
     * @param product  the product to visit
     */
    void VisitProduct(Product* product) override
    {
        mProducts.push_back(product);
    }

    /**
     * get the products stored in the local storage
     *
     * @return the products
     */
    std::vector<Product*> GetProducts() const { return mProducts; }
};

#endif //PRODUCTVISITOR_H
