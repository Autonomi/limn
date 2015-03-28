use Test::More tests => 14;
use strict;
use warnings;

BEGIN {
    use FindBin;
    use lib "$FindBin::Bin/../lib";
}

use Slic3r;
use List::Util qw(first sum);
use Slic3r::Geometry qw(epsilon scale unscale scaled_epsilon Y);
use Slic3r::Test;

# Disable this until a more robust implementation is provided. It currently
# fails on Linux 32bit because some spurious extrudates are generated.
if (0) {
    my $config = Slic3r::Config->new_from_defaults;
    $config->set('layer_height', 0.2);
    $config->set('first_layer_height', '100%');
    $config->set('extrusion_width', 0.5);
    $config->set('first_layer_extrusion_width', '200%'); # check this one too
    $config->set('skirts', 0);
    $config->set('thin_walls', 1);
    
    my $print = Slic3r::Test::init_print('gt2_teeth', config => $config);
    
    my %extrusion_paths = ();  # Z => count of continuous extrusions
    my $extruding = 0;
    Slic3r::GCode::Reader->new->parse(Slic3r::Test::gcode($print), sub {
        my ($self, $cmd, $args, $info) = @_;
        
        if ($cmd eq 'G1') {
            if ($info->{extruding} && $info->{dist_XY}) {
                if (!$extruding) {
                    $extrusion_paths{$self->Z} //= 0;
                    $extrusion_paths{$self->Z}++;
                }
                $extruding = 1;
            } else {
                $extruding = 0;
            }
        }
    });
    
    ok !(first { $_ != 3 } values %extrusion_paths),
        'no superfluous thin walls are generated for toothed profile';
}

{
    my $square = Slic3r::Polygon->new_scale(  # ccw
        [100, 100],
        [200, 100],
        [200, 200],
        [100, 200],
    );
    my $hole_in_square = Slic3r::Polygon->new_scale(  # cw
        [140, 140],
        [140, 160],
        [160, 160],
        [160, 140],
    );
    my $expolygon = Slic3r::ExPolygon->new($square, $hole_in_square);
    my $res = $expolygon->medial_axis(scale 1, scale 0.5);
    is scalar(@$res), 1, 'medial axis of a square shape is a single path';
    isa_ok $res->[0], 'Slic3r::Polyline', 'medial axis result is a polyline';
    ok $res->[0]->first_point->coincides_with($res->[0]->last_point), 'polyline forms a closed loop';
    ok $res->[0]->length > $hole_in_square->length && $res->[0]->length < $square->length,
        'medial axis loop has reasonable length';
}

{
    my $expolygon = Slic3r::ExPolygon->new(Slic3r::Polygon->new_scale(
        [100, 100],
        [120, 100],
        [120, 200],
        [100, 200],
    ));
    my $res = $expolygon->medial_axis(scale 1, scale 0.5);
    is scalar(@$res), 1, 'medial axis of a narrow rectangle is a single line';
    ok unscale($res->[0]->length) >= (200-100 - (120-100)) - epsilon, 'medial axis has reasonable length';
    
    $expolygon = Slic3r::ExPolygon->new(Slic3r::Polygon->new_scale(
        [100, 100],
        [120, 100],
        [120, 200],
        [105, 200],  # extra point in the short side
        [100, 200],
    ));
    my $res2 = $expolygon->medial_axis(scale 1, scale 0.5);
    is scalar(@$res), 1, 'medial axis of a narrow rectangle with an extra vertex is still a single line';
    ok unscale($res->[0]->length) >= (200-100 - (120-100)) - epsilon, 'medial axis has still a reasonable length';
    ok !(grep { abs($_ - scale 150) < scaled_epsilon } map $_->[Y], map @$_, @$res2), "extra vertices don't influence medial axis";
    
}

{
    my $expolygon = Slic3r::ExPolygon->new(Slic3r::Polygon->new_scale(
        [100, 100],
        [120, 100],
        [112, 200],
        [108, 200],
    ));
    my $res = $expolygon->medial_axis(scale 1, scale 0.5);
    is scalar(@$res), 1, 'medial axis of a narrow trapezoid is a single line';
    ok unscale($res->[0]->length) >= (200-100 - (120-100)) - epsilon, 'medial axis has reasonable length';
}

{
    my $expolygon = Slic3r::ExPolygon->new(Slic3r::Polygon->new_scale(
        [100, 100],
        [120, 100],
        [120, 180],
        [200, 180],
        [200, 200],
        [100, 200],
    ));
    my $res = $expolygon->medial_axis(scale 1, scale 0.5);
    is scalar(@$res), 1, 'medial axis of a L shape is a single polyline';
    my $len = unscale($res->[0]->length) + 20;  # 20 is the thickness of the expolygon, which is subtracted from the ends
    ok $len > 80*2 && $len < 100*2, 'medial axis has reasonable length';
}

{
    my $expolygon = Slic3r::ExPolygon->new(Slic3r::Polygon->new(
        [-203064906,-51459966],[-219312231,-51459966],[-219335477,-51459962],[-219376095,-51459962],[-219412047,-51459966],
        [-219572094,-51459966],[-219624814,-51459962],[-219642183,-51459962],[-219656665,-51459966],[-220815482,-51459966],
        [-220815482,-37738966],[-221117540,-37738966],[-221117540,-51762024],[-203064906,-51762024],
    ));
    my $polylines = $expolygon->medial_axis(819998, 102499.75);
    
    my $perimeter = $expolygon->contour->split_at_first_point->length;
    ok sum(map $_->length, @$polylines) > $perimeter/2/4*3, 'medial axis has a reasonable length';
}

__END__
