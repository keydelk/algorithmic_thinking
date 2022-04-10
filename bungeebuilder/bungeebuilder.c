/* bungeebuilder.c
 * A new bungee jumping attraction is to be built at a mountain range of N mountains of
 * heights H1,H2,…,HN. This project involves constructing a horizontal bridge connecting two 
 * distinct mountains, on which the attraction will be opened. The bridge may be built at any
 * height up to the minimum of the two connecting mountains as long as it is strictly higher than
 * all mountains between the two.
 *
 * Once the bridge is built, the attraction will be opened at some point along it. The jumping
 * distance is limited by the vertical distance of the attraction from the ground directly below.
 * In order to achieve the greatest level of excitement, the bridge should be built to maximise
 * the distance of the furthest point from the ground.A new bungee jumping attraction is to be 
 * built at a mountain range of N mountains of heights H1,H2,…,HN. This project involves
 * constructing a horizontal bridge connecting two distinct mountains, on which the attraction
 * will be opened. The bridge may be built at any height up to the minimum of the two connecting
 * mountains as long as it is strictly higher than all mountains between the two.
 * Once the bridge is built, the attraction will be opened at some point along it. The jumping
 * distance is limited by the vertical distance of the attraction from the ground directly below.
 * In order to achieve the greatest level of excitement, the bridge should be built to maximise
 * the distance of the furthest point from the ground.
 *
 * Input: The first line contains an integer N (1≤N≤106), the number of mountains.
 * The second line contains N integers H1,H2,…,HN where Hi (0≤Hi≤109) denotes the height of the
 * ith mountain.
 *
 * Output: The maximum jumping distance possible.
 *
 * Variables: n = the number of mountains, h = height of current mountain, p = height of previous peak,
 *            v = depth of lowest valley since previous peak, bh = bridge heigh = lower(h,p),
 *            jump = biggest jump on this bridge = bh - v, max_jump = biggest jump on mountain range
 */

#include <stdio.h>
#include <stdlib.h>

int min(int a, int b);
int max(int a, int b);

int main(){
  int n = 0, h = 0, p = 0, v = 0, bh = 0, jump = 0, max_jump = 0;
  
  scanf("%d", &n);

  for(int i = 0; i < n; i++){
    scanf("%d", &h);

    if(h >= p){
      bh = min(h,p);
      jump = bh - v;
      max_jump = max(jump, max_jump);

      p = h;
      v = h;
    } else {
      v = min(v, h);
      
      if(h >= v){
        bh = min(h,p);
        jump = bh - v;
        max_jump = max(jump, max_jump);
      }
    }
  }


  printf("%d", max_jump);

  return EXIT_SUCCESS;
}

int min(int a, int b){
  if(a<b){
    return a;
  }
  return b;
}

int max(int a, int b){
  if(a>b){
    return a;
  }
  return b;
}