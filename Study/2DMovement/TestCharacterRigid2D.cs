using System;
using System.Collections.Generic;
using UnityEngine;

public enum GroundStateType{
    Ground,
    Air
}

public enum LocoStateType{  //virtual player 만들어서 애니메이터 연동, enum 위치도 player로 이동
    Walk,
    Run,
    Idle,
    Fall
}

[RequireComponent(typeof(Rigidbody2D), typeof(CapsuleCollider2D))]
public class TestCharacterRigid2D : MonoBehaviour
{
    [SerializeField] private Rigidbody2D rb;
    [SerializeField] private CapsuleCollider2D capsule;
    [SerializeField] private float GravitySpeed = 0.0f;

    private Vector2 FinalVelocity;

    public event Action OnGroundLand;
    public event Action OnJumpStopped;

    public event Action<Vector2&> OnVectorChange;

    private void Awake() {
        if(rb == null)  rb = GetComponent<Rigidbody2D>();
        if(capsule == null) capsule = GetComponent<CapsuleCollider2D>();
    }

    private void FixedUpdate(){
        FinalVelocity = new Vector2(0.0f, 0.0f);
        applyGroundState();
        applyMoveCommand();
        rb.MovePosition(rb.position + FinalVelocity);
    }

    public void AddVertical(float y){
        
    }


    public void AddHorizontal(float x){

    }

    public void ScaleVertical(float y){
        
    }


    public void ScaleHorizontal(float x){

    }
    
    private void applyGroundState(){
        switch(getGroundState){
            case GroundStateType.Ground : 
                break;

            case GroundStateType.Air : 
                break;
        }
    }

    private void applyMoveCommand(){
        OnVectorChange(FinalVelocity);
    }

    private GroundStateType getGroundState{
        get{
            return GroundStateType.Ground;
        }
    }

    

}
