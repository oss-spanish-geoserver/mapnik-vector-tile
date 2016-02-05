#include "catch.hpp"

// mvt
#include "vector_tile_is_valid.hpp"

// protozero
#include <protozero/pbf_writer.hpp>

#include "vector_tile.pb.h"

typedef std::set<mapnik::vector_tile_impl::validity_error> error_set_T;

TEST_CASE( "invalid empty feature" )
{
    std::string buffer;
    vector_tile::Tile_Feature feature;
    error_set_T errs;

    feature.SerializeToString(&buffer);
    protozero::pbf_reader pbf_feature(buffer);

    feature_is_valid(pbf_feature, errs);

    CHECK(errs.empty() == false);
    CHECK(errs.count(mapnik::vector_tile_impl::validity_error::FEATURE_IS_EMPTY) == 1);
}

TEST_CASE( "invalid geometry without type" )
{
    std::string buffer;
    vector_tile::Tile_Feature feature;
    error_set_T errs;

    feature.add_geometry(9); // move_to | (1 << 3)
    feature.add_geometry(protozero::encode_zigzag32(5));
    feature.add_geometry(protozero::encode_zigzag32(5));

    feature.SerializeToString(&buffer);
    protozero::pbf_reader pbf_feature(buffer);

    feature_is_valid(pbf_feature, errs);

    CHECK(errs.empty() == false);
    CHECK(errs.count(mapnik::vector_tile_impl::validity_error::FEATURE_NO_GEOM_TYPE) == 1);
}

TEST_CASE( "valid raster feature" )
{
    std::string buffer;
    vector_tile::Tile_Feature feature;
    error_set_T errs;

    feature.set_raster("raster-blaster");

    feature.SerializeToString(&buffer);
    protozero::pbf_reader pbf_feature(buffer);

    feature_is_valid(pbf_feature, errs);

    CHECK(errs.empty() == true);
}

TEST_CASE( "valid geometry feature" )
{
    std::string buffer;
    vector_tile::Tile_Feature feature;
    error_set_T errs;

    feature.set_type(vector_tile::Tile_GeomType::Tile_GeomType_POINT);
    feature.add_geometry(9); // move_to | (1 << 3)
    feature.add_geometry(protozero::encode_zigzag32(5));
    feature.add_geometry(protozero::encode_zigzag32(5));

    feature.SerializeToString(&buffer);
    protozero::pbf_reader pbf_feature(buffer);

    feature_is_valid(pbf_feature, errs);

    CHECK(errs.empty() == true);
}

TEST_CASE( "valid geometry feature" )
{
    std::string buffer;
    vector_tile::Tile_Feature feature;
    error_set_T errs;

    feature.set_type(vector_tile::Tile_GeomType::Tile_GeomType_POINT);
    feature.add_geometry(9); // move_to | (1 << 3)
    feature.add_geometry(protozero::encode_zigzag32(5));
    feature.add_geometry(protozero::encode_zigzag32(5));

    feature.SerializeToString(&buffer);
    protozero::pbf_reader pbf_feature(buffer);

    feature_is_valid(pbf_feature, errs);

    CHECK(errs.empty() == true);
}
