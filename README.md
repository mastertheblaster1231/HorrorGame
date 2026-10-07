** Need to create a Inventory Item Component **
Inside  It create a     UStaticMeshComponent* Mesh; in side it
And Add 

public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName ItemID;

    UStaticMeshComponent* GetMesh() const
    {
        return Mesh;
    }
need to add 
1) pickup and throw mechanism
2) need to add Gun  Actors\
3) Swap weapons in player hand
4) none, unharmed,  pistol , ShotGun,  Rifle.
5) basic  inspect animation reference : -   https://youtu.be/676EOHTBd7E?si=th2mSS_0tAuO7BYK
6)  procedural gun code reference  :  https://www.firgelliauto.com/blogs/engineering-calculators/recoil-energy-calculator?srsltid=AU7gw4V67Cg0BsN2vv8kWUruldviojvK0EGi7pJfYb5PCibw1Etkq42Y
