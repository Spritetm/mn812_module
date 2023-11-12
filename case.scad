mod_flange_h=177;
mod_flange_d=10;
mod_h=153;
mod_w=172;
mod_d=55;
rad=(18.2/2); //fits an 18650
th=2;
flange_rest_th=5;
screws_dist=87;
screws_inset=3;
insert_h=4.5; //actually 4 but we want somewhere for the melted material to go
insert_d=4.9; //actually 5 but we want some extra material

case();

module insert_hole() {
    translate([0,0,-insert_h]) cylinder(d=insert_d, h=insert_h+1);
}

module case() {
    difference() {
        translate([-rad-th, -rad-th, -th]) rounded_cube([mod_flange_h+rad*2+th*2, mod_w+rad*2+th*2, mod_d+th*2], rad+th);
        difference() {
        translate([-rad, -rad, 0]) rounded_cube([mod_flange_h+rad*2, mod_w+rad*2, mod_d-mod_flange_d-flange_rest_th], rad);
            translate([-15,-10+(mod_w/2-screws_dist/2),0]) cube([30,20,mod_h]);
            translate([-15,-10+(mod_w/2+screws_dist/2),0]) cube([30,20,mod_h]);
            translate([-15+mod_flange_h,-10+(mod_w/2-screws_dist/2),0]) cube([30,20,mod_h]);
            translate([-15+mod_flange_h,-10+(mod_w/2+screws_dist/2),0]) cube([30,20,mod_h]);
        }
        translate([(mod_flange_h-mod_h)/2,0,th]) cube([mod_h, mod_w, mod_d-flange_rest_th]);
        translate([0,0,mod_d-mod_flange_d]) cube([mod_flange_h, mod_w, mod_d]);
        translate([screws_inset,(mod_w/2-screws_dist/2),mod_d-mod_flange_d]) insert_hole();
        translate([screws_inset,(mod_w/2+screws_dist/2),mod_d-mod_flange_d]) insert_hole();
        translate([mod_flange_h-screws_inset,(mod_w/2-screws_dist/2),mod_d-mod_flange_d]) insert_hole();
        translate([mod_flange_h-screws_inset,(mod_w/2+screws_dist/2),mod_d-mod_flange_d]) insert_hole();

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
