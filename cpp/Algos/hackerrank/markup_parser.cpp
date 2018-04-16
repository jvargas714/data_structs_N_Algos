#include "markup_parser.h"
#include "utility.h"

// for now ignoring case when there is a space between '<' and 'tag1'
void collect_tag_values( std::vector<std::string>& tokens,
                         const std::string& curr_token,
                         tag_map& t_map )
{
    val_pair vp;
    val_pairs vps;
    if ( tokens.size() < 3 )
        return;

    for ( int i = 1; i < tokens.size(); i+=3 )  // name = value name1 = value1
    {
        if( tokens[i+1] == "=" )
        {
            std::string val = tokens[i+2];
            val.erase( std::remove( val.begin(), val.end(), '\"' ), val.end() );
            size_t found = val.find( '>' );
            if( found != std::string::npos )
            {
                val = val.substr( 0, found );
            }
            vps.push_back( val_pair( tokens[i], val ) );
        }
    }
    t_map[curr_token] = vps;
}

void pop_attr_map( tag_map& attr_map, const int& num_lines )
{
    std::string line;
    std::string current_tag = "";
    std::vector<std::string> tags;
    bool tag_terminated = true;

    for( int i = 0; i < num_lines; i++ )
    {
        getline( std::cin, line );
        if( line.empty() )
            continue;
        line = elim_whitespace( line );
        std::vector<std::string> tokens = split( line, ' ' );

        // check for end of tag
        if( tokens.size() && tokens[0][1] != '/' )   // process tag attributes here
        {

            if( tokens.size() == 1 )
                current_tag = tokens[0].substr( 1, tokens[0].size()-2 );
            else
                current_tag = tokens[0].substr(1);

            tags.push_back( current_tag );
            current_tag = build_tag( tags );
            collect_tag_values( tokens, current_tag, attr_map );
        }
        else                        // terminate tag here
        {
            tags.pop_back();
            current_tag = "";
        }
    }
}

void process_queries( tag_map& attr_map, const int& q )
{
    tag_map::iterator it;
    val_pairs attr_pairs;
    for( int i = 0; i < q; ++i )
    {
        std::string query_line;
        if( !std::getline( std::cin, query_line ) )
            std::cerr << "Error reading query, continuing to next one." << std::endl;

        if( query_line.empty() )
            continue;

        std::vector<std::string> query_v = split( query_line, QUERY_DELIM );
        // output query results
        it = attr_map.find( query_v[0] );
        if( it == attr_map.end() )
        {
            std::cout << QUERY_FAIL << std::endl;
        }
        else
        {
            tag attr = query_v[1];
            attr_pairs = attr_map[ query_v[0] ];
            val_pairs::const_iterator c_it = get_attr( attr_pairs, attr );
            if( c_it == attr_pairs.end() )
                std::cout << QUERY_FAIL << std::endl;
            else
                std::cout << c_it->second << std::endl;
        }
    }
}

val_pairs::const_iterator get_attr( const val_pairs& v_pairs, const std::string& attr )
{
    return
        std::find_if( v_pairs.begin(), v_pairs.end(), [ attr ]( val_pair vp )
            {
                return vp.first == attr;
            }
        );
}

tag build_tag( const std::vector<tag>& tags )
{
    tag result = tags[0];
    if( tags.size() == 1 )
        return result;

    for( auto it = tags.begin()+1; it != tags.end(); ++it )
        result += "." + *it;
    return result;
}


//------------------------------------Display functions---------------------------------------------
void display( const val_pairs& vps )
{
    for( auto& el : vps )
    {
        std::cout << "name: " << el.first << " value: " << el.second << std::endl;
    }
}

void display( const std::vector<std::string>& items )
{
    for( auto& item : items )
        std::cout << item << "...";
    std::cout << std::endl;
}

void display( const tag_map& tmap )
{
    for( auto& el : tmap )
    {
        std::string tag = el.first;
        std::cout << "[" << tag << "]" << " ";
        for( auto& key_val : el.second )
        {
            std::cout << key_val.first << "-->" << key_val.second << " ";
        }
        std::cout << std::endl;
    }
}
