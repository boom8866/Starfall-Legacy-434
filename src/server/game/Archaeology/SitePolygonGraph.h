/*
 * Copyright (C) 2008-2015 Nephyr Life-Binder <Vanzo Luca Samuele>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SITE_POLYGON_GRAPH_GENERATOR_H
#define SITE_POLYGON_GRAPH_GENERATOR_H

#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

//---------------------------------------------------------------------------//

template <typename Q>
struct SitePolygonGraphNode
{
public:
    SitePolygonGraphNode()
    {
        _pointX = Q();
        _pointY = Q();
    }

    void set(const SitePolygonGraphNode<Q> &node) { _pointX = node.getX(); _pointY = node.getY(); }

    void setX(const Q &x) { _pointX = x; }
    void setY(const Q &y) { _pointY = y; }

    const Q getX() const { return _pointX; }
    const Q getY() const { return _pointY; }

    const SitePolygonGraphNode<Q> get() const { return (*this); }

private:
    Q _pointX;
    Q _pointY;
};

//---------------------------------------------------------------------------//

template <typename Q>
struct SitePolygonGraphArch
{
public:
    SitePolygonGraphArch()
    {
        _pointAx = Q();
        _pointAy = Q();
        _pointBx = Q();
        _pointBy = Q();
    }

    void set(const SitePolygonGraphArch<Q> &arch)
    {
        _pointAx = arch.getAx();
        _pointAy = arch.getAy();
        _pointBx = arch.getBx();
        _pointBy = arch.getBy();
    }

    void setA(const SitePolygonGraphNode<Q> &node) { _pointAx = node.getX(); _pointAy = node.getY(); }
    void setB(const SitePolygonGraphNode<Q> &node) { _pointBx = node.getX(); _pointBy = node.getY(); }

    void setA(const Q &x, const Q &y) { _pointAx = x; _pointAy = y; }
    void setB(const Q &x, const Q &y) { _pointBx = x; _pointBy = y; }

    const Q getAx() const { return _pointAx; }
    const Q getAy() const { return _pointAy; }
    const Q getBx() const { return _pointBx; }
    const Q getBy() const { return _pointBy; }

    const SitePolygonGraphArch<Q> get() const { return (*this); }

private:
    Q _pointAx;
    Q _pointAy;

    Q _pointBx;
    Q _pointBy;
};

//---------------------------------------------------------------------------//

template <typename T>
class SitePolygonGraph
{
public:
    SitePolygonGraph()
    {
        _arches      = 0;
        _nodes       = 0;
        _size_nodes  = 0;
        _size_arches = 0;

        // use current time as seed for random generator
        std::srand(std::time(0));
    }

    ~SitePolygonGraph()
    {
        if(!_nodes) return;
        delete[] _nodes;

        if(!_arches) return;
        delete[] _arches;
    }

    void add_node(const SitePolygonGraphNode<T> &node)
    {
        if(!this->resize())
            return;

        _nodes[_size_nodes - 1].setX(node.getX());
        _nodes[_size_nodes - 1].setY(node.getY());

        if(_size_nodes > 1)
            this->calculate_arches();
    }

    void add_node(const T &x, const T &y)
    {
        if(!this->resize())
            return;

        _nodes[_size_nodes - 1].setX(x);
        _nodes[_size_nodes - 1].setY(y);

        if(_size_nodes > 1)
            this->calculate_arches();
    }

    SitePolygonGraphNode<T> randomize_poi()
    {
        SitePolygonGraphNode<T> poi_node;

        if(_arches <= 0 || _nodes <= 0)
            return poi_node;

        index_type i_poi = std::rand() % _size_arches;
        float i_segment  = ((float) std::rand() / RAND_MAX);

        float x_segment  = _arches[i_poi].getAx() + i_segment * (_arches[i_poi].getBx() - _arches[i_poi].getAx());
        float y_segment  = _arches[i_poi].getAy() + i_segment * (_arches[i_poi].getBy() - _arches[i_poi].getAy());

        poi_node.setX(static_cast<T>(x_segment));
        poi_node.setY(static_cast<T>(y_segment));

        return poi_node;
    }

private:
    bool calculate_arches()
    {
        if(_size_nodes <= 0)
            return false;

        SitePolygonGraphArch<T>* tmpArches = _arches;
        index_type tmpSizeArches           = _size_arches;

        try
        {
            _size_arches = (_size_nodes * (_size_nodes - 1)) / 2;
            _arches      = new SitePolygonGraphArch<T>[_size_arches];
            index_type i = 0;

            for(i = 0; i < tmpSizeArches; i++)
                _arches[i].set(tmpArches[i].get());

            for(index_type n = 0; n < _size_nodes - 1; n++)
            {
                _arches[ i ].setB(_nodes[_size_nodes - 1].get());
                _arches[i++].setA(_nodes[n].get());
            }

            delete[] tmpArches;
        }
        catch(...)
        {
            _arches      = tmpArches;
            _size_arches = tmpSizeArches;

            return false;
        }

        return true;
    }

    bool resize()
    {
        SitePolygonGraphNode<value_type>* tmpNodes = _nodes;
        index_type tmpSize                         = _size_nodes++;
        _nodes                                     = 0;

        try
        {
            if(_size_nodes > 0) _nodes = new SitePolygonGraphNode<value_type>[_size_nodes];
            else _nodes                = 0;

            for(index_type i = 0; i < tmpSize; i++)
                _nodes[i].set(tmpNodes[i].get());

            delete[] tmpNodes;
        }
        catch(...)
        {
            _nodes      = tmpNodes;
            _size_nodes = tmpSize;

            return false;
        }

        return true;
    }

    typedef unsigned int index_type;
    typedef T value_type;

    SitePolygonGraphNode<T>* _nodes;
    SitePolygonGraphArch<T>* _arches;

    index_type _size_nodes;
    index_type _size_arches;
};

//---------------------------------------------------------------------------//

#endif  // SITE_POLYGON_GRAPH_GENERATOR_H
