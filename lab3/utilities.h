#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

    ///     cout<<pii(x,y);
    #define pii pair<int,int>
    template < typename F, typename S >
    ostream& operator << ( ostream& os, const pair< F, S > & p )
    {
        return os << "(" << p.first << ", " << p.second << ")";
    }

    ///     cout<<vector;
    template < typename T >
    ostream &operator << ( ostream & os, const vector< T > &v )
    {
        os << "{";
        typename vector< T > :: const_iterator it;
        for( it = v.begin(); it != v.end(); it++ )
        {
            if( it != v.begin() ) os << ", ";
            os << *it;
        }
        return os << "}";
    }

    ///     cout<<set;
    template < typename T >
    ostream &operator << ( ostream & os, const set< T > &v )
    {
        os << "[";
        typename set< T > :: const_iterator it;
        for ( it = v.begin(); it != v.end(); it++ )
        {
            if( it != v.begin() ) os << ", ";
            os << *it;
        }
        return os << "]";
    }

    ///     cout<<map;
    template < typename F, typename S >
    ostream &operator << ( ostream & os, const map< F, S > &v )
    {
        os << "[";
        typename map< F , S >::const_iterator it;
        for( it = v.begin(); it != v.end(); it++ )
        {
            if( it != v.begin() ) os << ", ";
            os << it -> first << " = " << it -> second ;
        }
        return os << "]";
    }

    ///     debug(x);
    #define debug(x) cerr << #x << " = " << x << endl;



#endif // UTILITIES_H_INCLUDED
