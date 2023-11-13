mod_flange_h=179;
mod_flange_d=10;
mod_h=163;
mod_w=174;
mod_d=55;
rad=(18.2/2); //fits an 18650
th=1.2;
flange_rest_th=5;
screws_dist=87;
screws_inset=3;
insert_h=4.5; //actually 4 but we want somewhere for the melted material to go
insert_d=4.9; //actually 5 but we want some extra material

split_h=15;


holes_pos=[
    [screws_inset,(mod_w/2-screws_dist/2)],
    [screws_inset,(mod_w/2+screws_dist/2)],
    [mod_flange_h-screws_inset,(mod_w/2-screws_dist/2)],
    [mod_flange_h-screws_inset,(mod_w/2+screws_dist/2)],
];


//translate([0,0,-50]) case_bot();
case_top();

$fs=0.1;
$fa=8;

margin=0.2;

module case_top() {
    difference() {
        intersection() {
            case();
            translate([-20, -20, split_h]) cube([250, 250, 100]);
        }
        for (p=holes_pos) {
            translate([p.x, p.y, split_h]) rotate([180,0,0]) insert_hole();
        }
        intersection() {
            difference() {
                translate([-rad-margin, -rad-margin, 0]) rounded_cube([mod_flange_h+rad*2+margin*2, mod_w+rad*2+margin*2, mod_d-mod_flange_d-flange_rest_th], rad);
                translate([-rad+th+margin, -rad+th+margin, th]) rounded_cube([mod_flange_h+rad*2-th*2-margin*2, mod_w+rad*2-th*2-margin*2, mod_d-th*2], rad-th);
            }
            translate([-20, -20, 0]) cube([250, 250, split_h+3+margin]);
        }
        translate([6,190,30]) rotate([90,0,0]) cylinder(d=10.5, h=10);
    }
}

module case_bot() {
    difference() {
        case_bot_flange();

        for (p=holes_pos) {
            translate([p.x, p.y, 2]) cylinder(h=split_h, d=3.2);
            translate([p.x, p.y, -2]) cylinder(h=split_h, d=6);
        }
    }
}

module case_bot_flange() {
    difference() {
        case();
        translate([-20, -20, split_h]) cube([250, 250, 100]);
    }

    intersection() {
        difference() {
            translate([-rad, -rad, 0]) rounded_cube([mod_flange_h+rad*2, mod_w+rad*2, mod_d-mod_flange_d-flange_rest_th], rad);
            translate([-rad+th, -rad+th, th]) rounded_cube([mod_flange_h+rad*2-th*2, mod_w+rad*2-th*2, mod_d-th*2], rad-th);
        }
        translate([-20, -20, 0]) cube([250, 250, split_h+3]);
    }
}


module insert_hole() {
    translate([0,0,-insert_h]) cylinder(d=insert_d, h=insert_h+1);
}


module case() {
    difference() {
        translate([-rad-th, -rad-th, -th]) rounded_cube([mod_flange_h+rad*2+th*2, mod_w+rad*2+th*2, mod_d+th*2], rad+th);
        difference() {
        translate([-rad, -rad, 0]) rounded_cube([mod_flange_h+rad*2, mod_w+rad*2, mod_d], rad);
            translate([-15,-10+(mod_w/2-screws_dist/2),0]) cube([30,20,mod_h]);
            translate([-15,-10+(mod_w/2+screws_dist/2),0]) cube([30,20,mod_h]);
            translate([-15+mod_flange_h,-10+(mod_w/2-screws_dist/2),0]) cube([30,20,mod_h]);
            translate([-15+mod_flange_h,-10+(mod_w/2+screws_dist/2),0]) cube([30,20,mod_h]);
        }
        translate([(mod_flange_h-mod_h)/2,0,th]) cube([mod_h, mod_w, mod_d-flange_rest_th]);
        translate([0,0,mod_d-mod_flange_d]) cube([mod_flange_h, mod_w, mod_d]);
        for (p=holes_pos) {
            translate([p.x, p.y,mod_d-mod_flange_d]) insert_hole();
        }
    }
}

module rounded_cube(size, r) {
    hull() {
        translate([r, r, r]) sphere(r=r);
        translate([size.x-r, r, r]) sphere(r=r);
        translate([r, size.y-r, r]) sphere(r=r);
        translate([size.x-r, size.y-r, r]) sphere(r=r);
        translate([r, r, size.z-r]) sphere(r=r);
        translate([size.x-r, r, size.z-r]) sphere(r=r);
        translate([r, size.y-r, size.z-r]) sphere(r=r);
        translate([size.x-r, size.y-r, size.z-r]) sphere(r=r);
    }
}
