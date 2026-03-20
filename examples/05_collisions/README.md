# Moving Square Project (Notes for Future Me)

Took about 3 hours to get this organized, but honestly, I feel like a genius right now. 

The "Inverse Rotation" trick is cool. Instead of trying to calculate which pixels fit into a tilted square (which sounds like a nightmare), you just take a pixel on the screen and "un-spin" it. If that "ghost" version of the pixel lands in the original straight square, you color it in. It feels like cheating, but it’s actually just smart math.


### Modularity & Clean Code:
I spent a good chunk of time moving everything out of `main`. Now it's way more "functional" breaking stuff into their own functions so it’s not a cluttered mess. This should make it way easier to prototype 3D stuff or physics sims later. 

### Physics vs. Graphics:
I’m was unsure how they overlap but kinda starting to see how they overlap. Light is literally physics, so getting the math right for a 2D square is just the first step toward making physically accurate simulations with good graphics. It’s all just simple math at the end of the day.

---

*Check the Atlas GitHub repo for the graphs and the screen recordings if you forget how the coordinate shifts work.*