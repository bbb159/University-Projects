package application;

import application.model.OpcoesMenu;
import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;
import io.grpc.StatusRuntimeException;
import io.grpc.stub.StreamObserver;
import org.socketUdp.grpc.MakeOperationGrpc;
import org.socketUdp.grpc.Operation;
import org.socketUdp.grpc.OperationResponse;

import java.io.UnsupportedEncodingException;
import java.math.BigInteger;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;
import java.util.stream.Stream;

public class ClientGrpc {
    private final ManagedChannel channel;
    private final MakeOperationGrpc.MakeOperationStub stub;

    public ClientGrpc(String host, int port){
        this(ManagedChannelBuilder.forAddress(host, port)
                .usePlaintext()
                .build());
    }

    ClientGrpc(ManagedChannel channel) {
        this.channel = channel;
        stub = MakeOperationGrpc.newStub(channel);
    }

    public void shutdown() throws InterruptedException {
        channel.shutdown().awaitTermination(5, TimeUnit.SECONDS);
    }

    public void makeOperation(int op, Integer chave, String valor) throws UnsupportedEncodingException {
        BigInteger chaveNova;

        try{
            chaveNova = BigInteger.valueOf(chave.intValue());
        }catch (Exception ex){
            System.out.println(ex.getMessage());
            return;
        }
        
        final Operation operation = Operation.newBuilder()
                .setOp(op)
                .setTamChave(chaveNova.toByteArray().length)
                .setChave(chave)
                .setTamValor(valor.getBytes("UTF-16").length-2)
                .setValor(valor)
                .build();
        StreamObserver<OperationResponse> response = new StreamObserver<OperationResponse>() {
            @Override
            public void onNext(OperationResponse operationResponse) {
                System.out.println(operationResponse.getValor()+ " " + operationResponse.getResponse());
            }

            @Override
            public void onError(Throwable throwable) {

            }

            @Override
            public void onCompleted() {
                System.out.println("Disconnected");
            }
        };
        try {
            stub.makeOperation(operation, response);
        } catch (StatusRuntimeException e) {
            System.out.println(e.getMessage());
            return;
        }
    }


    public static void main(String[] args) throws InterruptedException, UnsupportedEncodingException {
        ClientGrpc client = new ClientGrpc("localhost", 8090);
        Scanner scanner = new Scanner(System.in);

        Integer opcaoMenu = 4;
        Integer chave = 0;
        String valor = "";
        try {


            while (true) {
                //------- MENU
                opcaoMenu = imprimirMenu(opcaoMenu, scanner);
                //----------------------------------
                if(opcaoMenu==10)
                    break;

                //------- RECEBER CHAVE E VALOR
                System.out.println("--------------------");
                System.out.println("Digite a chave:");
                chave = scanner.nextInt();

                if (opcaoMenu == OpcoesMenu.CREATE.getValor() || opcaoMenu == OpcoesMenu.UPDATE.getValor()) {
                    System.out.println("Digite o valor ");
                    valor = scanner.next();
                }

                client.makeOperation(opcaoMenu, chave, valor);
            }


        } finally {
            client.shutdown();
        }
    }

    public static int imprimirMenu(int opcao, Scanner scanner){
        do {
            OpcoesMenu[] menu = OpcoesMenu.values();
            for (OpcoesMenu m : menu) {
                System.out.printf("[%d] - %s%n", m.ordinal(), m.name());
            }
            System.out.println("Opção:");
            opcao = scanner.nextInt();
        }while ((opcao > 5 || opcao < 0) && opcao != 10);
        return opcao;
    }

}
