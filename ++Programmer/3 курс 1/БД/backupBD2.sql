PGDMP                      {         	   AS-21-1_2    12.9    16.0 x    �           0    0    ENCODING    ENCODING        SET client_encoding = 'UTF8';
                      false            �           0    0 
   STDSTRINGS 
   STDSTRINGS     (   SET standard_conforming_strings = 'on';
                      false            �           0    0 
   SEARCHPATH 
   SEARCHPATH     8   SELECT pg_catalog.set_config('search_path', '', false);
                      false            �           1262    66458 	   AS-21-1_2    DATABASE        CREATE DATABASE "AS-21-1_2" WITH TEMPLATE = template0 ENCODING = 'UTF8' LOCALE_PROVIDER = libc LOCALE = 'Russian_Russia.1251';
    DROP DATABASE "AS-21-1_2";
                pi19    false                        2615    2200    public    SCHEMA     2   -- *not* creating schema, since initdb creates it
 2   -- *not* dropping schema, since initdb creates it
                postgres    false            �           0    0    SCHEMA public    ACL     Q   REVOKE USAGE ON SCHEMA public FROM PUBLIC;
GRANT ALL ON SCHEMA public TO PUBLIC;
                   postgres    false    6            �            1259    66459 	   available    TABLE     t   CREATE TABLE public.available (
    name_color character varying(50) NOT NULL,
    id_equipment integer NOT NULL
);
    DROP TABLE public.available;
       public         heap    pi19    false    6            �            1259    66462    bill    TABLE     �   CREATE TABLE public.bill (
    id_bill integer NOT NULL,
    number_boocking integer NOT NULL,
    date_bill date NOT NULL,
    payment_summary_bill numeric,
    payment_date_bill date,
    invoice_account_bill numeric NOT NULL
);
    DROP TABLE public.bill;
       public         heap    pi19    false    6            �            1259    66468    bill_id_bill_seq    SEQUENCE     �   CREATE SEQUENCE public.bill_id_bill_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 '   DROP SEQUENCE public.bill_id_bill_seq;
       public          pi19    false    6    203            �           0    0    bill_id_bill_seq    SEQUENCE OWNED BY     E   ALTER SEQUENCE public.bill_id_bill_seq OWNED BY public.bill.id_bill;
          public          pi19    false    204            �            1259    66470    booking    TABLE     �   CREATE TABLE public.booking (
    number_booking integer NOT NULL,
    id_customer integer NOT NULL,
    id_manager integer NOT NULL,
    date_booking date NOT NULL
);
    DROP TABLE public.booking;
       public         heap    pi19    false    6            �            1259    66473    booking_number_boocking_seq    SEQUENCE     �   CREATE SEQUENCE public.booking_number_boocking_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 2   DROP SEQUENCE public.booking_number_boocking_seq;
       public          pi19    false    6    205            �           0    0    booking_number_boocking_seq    SEQUENCE OWNED BY     Z   ALTER SEQUENCE public.booking_number_boocking_seq OWNED BY public.booking.number_booking;
          public          pi19    false    206            �            1259    66475    can_put    TABLE     a   CREATE TABLE public.can_put (
    id_model integer NOT NULL,
    id_supplier integer NOT NULL
);
    DROP TABLE public.can_put;
       public         heap    pi19    false    6            �            1259    66478    car    TABLE     �   CREATE TABLE public.car (
    id_car integer NOT NULL,
    id_equipment integer NOT NULL,
    number_booking integer,
    id_request integer,
    name_color character varying(50) NOT NULL,
    vin_number character(17),
    price_sell numeric NOT NULL
);
    DROP TABLE public.car;
       public         heap    pi19    false    6            �            1259    66484    car_id_car_seq    SEQUENCE     �   CREATE SEQUENCE public.car_id_car_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 %   DROP SEQUENCE public.car_id_car_seq;
       public          pi19    false    208    6            �           0    0    car_id_car_seq    SEQUENCE OWNED BY     A   ALTER SEQUENCE public.car_id_car_seq OWNED BY public.car.id_car;
          public          pi19    false    209            �            1259    66486    color    TABLE     M   CREATE TABLE public.color (
    name_color character varying(50) NOT NULL
);
    DROP TABLE public.color;
       public         heap    pi19    false    6            �            1259    66489    customer    TABLE     �   CREATE TABLE public.customer (
    id_customer integer NOT NULL,
    passport_customer character(10),
    phone_customer character(10) NOT NULL,
    lfp_customer character varying(52) NOT NULL
);
    DROP TABLE public.customer;
       public         heap    pi19    false    6            �            1259    66492    customer_id_customer_seq    SEQUENCE     �   CREATE SEQUENCE public.customer_id_customer_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 /   DROP SEQUENCE public.customer_id_customer_seq;
       public          pi19    false    6    211            �           0    0    customer_id_customer_seq    SEQUENCE OWNED BY     U   ALTER SEQUENCE public.customer_id_customer_seq OWNED BY public.customer.id_customer;
          public          pi19    false    212            �            1259    66494 	   equipment    TABLE     �   CREATE TABLE public.equipment (
    id_equipment integer NOT NULL,
    id_model integer NOT NULL,
    price numeric NOT NULL,
    name_equipment character varying(50) NOT NULL
);
    DROP TABLE public.equipment;
       public         heap    pi19    false    6            �            1259    66500    equipment_id_equipment_seq    SEQUENCE     �   CREATE SEQUENCE public.equipment_id_equipment_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 1   DROP SEQUENCE public.equipment_id_equipment_seq;
       public          pi19    false    213    6            �           0    0    equipment_id_equipment_seq    SEQUENCE OWNED BY     Y   ALTER SEQUENCE public.equipment_id_equipment_seq OWNED BY public.equipment.id_equipment;
          public          pi19    false    214            �            1259    66502    manager    TABLE     �   CREATE TABLE public.manager (
    lfp_manager character varying(52) NOT NULL,
    id_manager integer NOT NULL,
    phone_manager character(10) NOT NULL
);
    DROP TABLE public.manager;
       public         heap    pi19    false    6            �            1259    66505    manager_id_manager_seq    SEQUENCE     �   CREATE SEQUENCE public.manager_id_manager_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 -   DROP SEQUENCE public.manager_id_manager_seq;
       public          pi19    false    6    215            �           0    0    manager_id_manager_seq    SEQUENCE OWNED BY     Q   ALTER SEQUENCE public.manager_id_manager_seq OWNED BY public.manager.id_manager;
          public          pi19    false    216            �            1259    66507    models    TABLE     �   CREATE TABLE public.models (
    id_model integer NOT NULL,
    brand_model character varying(50) NOT NULL,
    name_model character varying(50) NOT NULL
);
    DROP TABLE public.models;
       public         heap    pi19    false    6            �            1259    66510    models_id_model_seq    SEQUENCE     �   CREATE SEQUENCE public.models_id_model_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 *   DROP SEQUENCE public.models_id_model_seq;
       public          pi19    false    6    217            �           0    0    models_id_model_seq    SEQUENCE OWNED BY     K   ALTER SEQUENCE public.models_id_model_seq OWNED BY public.models.id_model;
          public          pi19    false    218            �            1259    66512    request    TABLE     �   CREATE TABLE public.request (
    id_request integer NOT NULL,
    id_manager integer NOT NULL,
    id_supplier integer NOT NULL,
    date_request date NOT NULL,
    number_request integer NOT NULL
);
    DROP TABLE public.request;
       public         heap    pi19    false    6            �            1259    66515    request_id_request_seq    SEQUENCE     �   CREATE SEQUENCE public.request_id_request_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 -   DROP SEQUENCE public.request_id_request_seq;
       public          pi19    false    6    219            �           0    0    request_id_request_seq    SEQUENCE OWNED BY     Q   ALTER SEQUENCE public.request_id_request_seq OWNED BY public.request.id_request;
          public          pi19    false    220            �            1259    66517    supplier    TABLE     �   CREATE TABLE public.supplier (
    id_supplier integer NOT NULL,
    address_supplier character varying(160),
    name_supplier character varying(50) NOT NULL
);
    DROP TABLE public.supplier;
       public         heap    pi19    false    6            �            1259    66520    supplier_id_supplier_seq    SEQUENCE     �   CREATE SEQUENCE public.supplier_id_supplier_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 /   DROP SEQUENCE public.supplier_id_supplier_seq;
       public          pi19    false    221    6            �           0    0    supplier_id_supplier_seq    SEQUENCE OWNED BY     U   ALTER SEQUENCE public.supplier_id_supplier_seq OWNED BY public.supplier.id_supplier;
          public          pi19    false    222            �
           2604    66522    bill id_bill    DEFAULT     l   ALTER TABLE ONLY public.bill ALTER COLUMN id_bill SET DEFAULT nextval('public.bill_id_bill_seq'::regclass);
 ;   ALTER TABLE public.bill ALTER COLUMN id_bill DROP DEFAULT;
       public          pi19    false    204    203            �
           2604    66523    booking number_booking    DEFAULT     �   ALTER TABLE ONLY public.booking ALTER COLUMN number_booking SET DEFAULT nextval('public.booking_number_boocking_seq'::regclass);
 E   ALTER TABLE public.booking ALTER COLUMN number_booking DROP DEFAULT;
       public          pi19    false    206    205            �
           2604    66524 
   car id_car    DEFAULT     h   ALTER TABLE ONLY public.car ALTER COLUMN id_car SET DEFAULT nextval('public.car_id_car_seq'::regclass);
 9   ALTER TABLE public.car ALTER COLUMN id_car DROP DEFAULT;
       public          pi19    false    209    208            �
           2604    66525    customer id_customer    DEFAULT     |   ALTER TABLE ONLY public.customer ALTER COLUMN id_customer SET DEFAULT nextval('public.customer_id_customer_seq'::regclass);
 C   ALTER TABLE public.customer ALTER COLUMN id_customer DROP DEFAULT;
       public          pi19    false    212    211            �
           2604    66526    equipment id_equipment    DEFAULT     �   ALTER TABLE ONLY public.equipment ALTER COLUMN id_equipment SET DEFAULT nextval('public.equipment_id_equipment_seq'::regclass);
 E   ALTER TABLE public.equipment ALTER COLUMN id_equipment DROP DEFAULT;
       public          pi19    false    214    213            �
           2604    66527    manager id_manager    DEFAULT     x   ALTER TABLE ONLY public.manager ALTER COLUMN id_manager SET DEFAULT nextval('public.manager_id_manager_seq'::regclass);
 A   ALTER TABLE public.manager ALTER COLUMN id_manager DROP DEFAULT;
       public          pi19    false    216    215            �
           2604    66528    models id_model    DEFAULT     r   ALTER TABLE ONLY public.models ALTER COLUMN id_model SET DEFAULT nextval('public.models_id_model_seq'::regclass);
 >   ALTER TABLE public.models ALTER COLUMN id_model DROP DEFAULT;
       public          pi19    false    218    217            �
           2604    66529    request id_request    DEFAULT     x   ALTER TABLE ONLY public.request ALTER COLUMN id_request SET DEFAULT nextval('public.request_id_request_seq'::regclass);
 A   ALTER TABLE public.request ALTER COLUMN id_request DROP DEFAULT;
       public          pi19    false    220    219            �
           2604    66530    supplier id_supplier    DEFAULT     |   ALTER TABLE ONLY public.supplier ALTER COLUMN id_supplier SET DEFAULT nextval('public.supplier_id_supplier_seq'::regclass);
 C   ALTER TABLE public.supplier ALTER COLUMN id_supplier DROP DEFAULT;
       public          pi19    false    222    221            �          0    66459 	   available 
   TABLE DATA           =   COPY public.available (name_color, id_equipment) FROM stdin;
    public          pi19    false    202   E�       �          0    66462    bill 
   TABLE DATA           �   COPY public.bill (id_bill, number_boocking, date_bill, payment_summary_bill, payment_date_bill, invoice_account_bill) FROM stdin;
    public          pi19    false    203   ��       �          0    66470    booking 
   TABLE DATA           X   COPY public.booking (number_booking, id_customer, id_manager, date_booking) FROM stdin;
    public          pi19    false    205   a�       �          0    66475    can_put 
   TABLE DATA           8   COPY public.can_put (id_model, id_supplier) FROM stdin;
    public          pi19    false    207   ��       �          0    66478    car 
   TABLE DATA           s   COPY public.car (id_car, id_equipment, number_booking, id_request, name_color, vin_number, price_sell) FROM stdin;
    public          pi19    false    208   b�       �          0    66486    color 
   TABLE DATA           +   COPY public.color (name_color) FROM stdin;
    public          pi19    false    210   7�       �          0    66489    customer 
   TABLE DATA           `   COPY public.customer (id_customer, passport_customer, phone_customer, lfp_customer) FROM stdin;
    public          pi19    false    211   4�       �          0    66494 	   equipment 
   TABLE DATA           R   COPY public.equipment (id_equipment, id_model, price, name_equipment) FROM stdin;
    public          pi19    false    213   ��       �          0    66502    manager 
   TABLE DATA           I   COPY public.manager (lfp_manager, id_manager, phone_manager) FROM stdin;
    public          pi19    false    215   1�       �          0    66507    models 
   TABLE DATA           C   COPY public.models (id_model, brand_model, name_model) FROM stdin;
    public          pi19    false    217   ��       �          0    66512    request 
   TABLE DATA           d   COPY public.request (id_request, id_manager, id_supplier, date_request, number_request) FROM stdin;
    public          pi19    false    219   �       �          0    66517    supplier 
   TABLE DATA           P   COPY public.supplier (id_supplier, address_supplier, name_supplier) FROM stdin;
    public          pi19    false    221   ��       �           0    0    bill_id_bill_seq    SEQUENCE SET     ?   SELECT pg_catalog.setval('public.bill_id_bill_seq', 25, true);
          public          pi19    false    204            �           0    0    booking_number_boocking_seq    SEQUENCE SET     J   SELECT pg_catalog.setval('public.booking_number_boocking_seq', 26, true);
          public          pi19    false    206            �           0    0    car_id_car_seq    SEQUENCE SET     =   SELECT pg_catalog.setval('public.car_id_car_seq', 50, true);
          public          pi19    false    209            �           0    0    customer_id_customer_seq    SEQUENCE SET     G   SELECT pg_catalog.setval('public.customer_id_customer_seq', 26, true);
          public          pi19    false    212            �           0    0    equipment_id_equipment_seq    SEQUENCE SET     I   SELECT pg_catalog.setval('public.equipment_id_equipment_seq', 27, true);
          public          pi19    false    214            �           0    0    manager_id_manager_seq    SEQUENCE SET     E   SELECT pg_catalog.setval('public.manager_id_manager_seq', 25, true);
          public          pi19    false    216            �           0    0    models_id_model_seq    SEQUENCE SET     B   SELECT pg_catalog.setval('public.models_id_model_seq', 28, true);
          public          pi19    false    218            �           0    0    request_id_request_seq    SEQUENCE SET     E   SELECT pg_catalog.setval('public.request_id_request_seq', 25, true);
          public          pi19    false    220            �           0    0    supplier_id_supplier_seq    SEQUENCE SET     G   SELECT pg_catalog.setval('public.supplier_id_supplier_seq', 25, true);
          public          pi19    false    222            �
           2606    66532    available pk_available 
   CONSTRAINT     j   ALTER TABLE ONLY public.available
    ADD CONSTRAINT pk_available PRIMARY KEY (name_color, id_equipment);
 @   ALTER TABLE ONLY public.available DROP CONSTRAINT pk_available;
       public            pi19    false    202    202            �
           2606    66534    bill pk_bill 
   CONSTRAINT     O   ALTER TABLE ONLY public.bill
    ADD CONSTRAINT pk_bill PRIMARY KEY (id_bill);
 6   ALTER TABLE ONLY public.bill DROP CONSTRAINT pk_bill;
       public            pi19    false    203            �
           2606    66536    booking pk_booking 
   CONSTRAINT     \   ALTER TABLE ONLY public.booking
    ADD CONSTRAINT pk_booking PRIMARY KEY (number_booking);
 <   ALTER TABLE ONLY public.booking DROP CONSTRAINT pk_booking;
       public            pi19    false    205            �
           2606    66538    can_put pk_can_put 
   CONSTRAINT     c   ALTER TABLE ONLY public.can_put
    ADD CONSTRAINT pk_can_put PRIMARY KEY (id_model, id_supplier);
 <   ALTER TABLE ONLY public.can_put DROP CONSTRAINT pk_can_put;
       public            pi19    false    207    207            �
           2606    66540 
   car pk_car 
   CONSTRAINT     L   ALTER TABLE ONLY public.car
    ADD CONSTRAINT pk_car PRIMARY KEY (id_car);
 4   ALTER TABLE ONLY public.car DROP CONSTRAINT pk_car;
       public            pi19    false    208            �
           2606    66542    color pk_color 
   CONSTRAINT     T   ALTER TABLE ONLY public.color
    ADD CONSTRAINT pk_color PRIMARY KEY (name_color);
 8   ALTER TABLE ONLY public.color DROP CONSTRAINT pk_color;
       public            pi19    false    210            �
           2606    66544    customer pk_customer 
   CONSTRAINT     [   ALTER TABLE ONLY public.customer
    ADD CONSTRAINT pk_customer PRIMARY KEY (id_customer);
 >   ALTER TABLE ONLY public.customer DROP CONSTRAINT pk_customer;
       public            pi19    false    211            �
           2606    66546    equipment pk_equipment 
   CONSTRAINT     ^   ALTER TABLE ONLY public.equipment
    ADD CONSTRAINT pk_equipment PRIMARY KEY (id_equipment);
 @   ALTER TABLE ONLY public.equipment DROP CONSTRAINT pk_equipment;
       public            pi19    false    213            �
           2606    66548    manager pk_manager 
   CONSTRAINT     X   ALTER TABLE ONLY public.manager
    ADD CONSTRAINT pk_manager PRIMARY KEY (id_manager);
 <   ALTER TABLE ONLY public.manager DROP CONSTRAINT pk_manager;
       public            pi19    false    215            �
           2606    66550    models pk_models 
   CONSTRAINT     T   ALTER TABLE ONLY public.models
    ADD CONSTRAINT pk_models PRIMARY KEY (id_model);
 :   ALTER TABLE ONLY public.models DROP CONSTRAINT pk_models;
       public            pi19    false    217            �
           2606    66552    request pk_request 
   CONSTRAINT     X   ALTER TABLE ONLY public.request
    ADD CONSTRAINT pk_request PRIMARY KEY (id_request);
 <   ALTER TABLE ONLY public.request DROP CONSTRAINT pk_request;
       public            pi19    false    219            �
           2606    66554    supplier pk_supplier 
   CONSTRAINT     [   ALTER TABLE ONLY public.supplier
    ADD CONSTRAINT pk_supplier PRIMARY KEY (id_supplier);
 >   ALTER TABLE ONLY public.supplier DROP CONSTRAINT pk_supplier;
       public            pi19    false    221            �
           1259    66555    available2_fk    INDEX     K   CREATE INDEX available2_fk ON public.available USING btree (id_equipment);
 !   DROP INDEX public.available2_fk;
       public            pi19    false    202            �
           1259    66556    available_fk    INDEX     H   CREATE INDEX available_fk ON public.available USING btree (name_color);
     DROP INDEX public.available_fk;
       public            pi19    false    202            �
           1259    66557    available_pk    INDEX     ]   CREATE UNIQUE INDEX available_pk ON public.available USING btree (name_color, id_equipment);
     DROP INDEX public.available_pk;
       public            pi19    false    202    202            �
           1259    66558    bill_pk    INDEX     B   CREATE UNIQUE INDEX bill_pk ON public.bill USING btree (id_bill);
    DROP INDEX public.bill_pk;
       public            pi19    false    203            �
           1259    66559    booking_date_index    INDEX     N   CREATE INDEX booking_date_index ON public.booking USING btree (date_booking);
 &   DROP INDEX public.booking_date_index;
       public            pi19    false    205            �
           1259    66560 
   booking_pk    INDEX     O   CREATE UNIQUE INDEX booking_pk ON public.booking USING btree (number_booking);
    DROP INDEX public.booking_pk;
       public            pi19    false    205            �
           1259    66561    can_put2_fk    INDEX     F   CREATE INDEX can_put2_fk ON public.can_put USING btree (id_supplier);
    DROP INDEX public.can_put2_fk;
       public            pi19    false    207            �
           1259    66562 
   can_put_fk    INDEX     B   CREATE INDEX can_put_fk ON public.can_put USING btree (id_model);
    DROP INDEX public.can_put_fk;
       public            pi19    false    207            �
           1259    66563 
   can_put_pk    INDEX     V   CREATE UNIQUE INDEX can_put_pk ON public.can_put USING btree (id_model, id_supplier);
    DROP INDEX public.can_put_pk;
       public            pi19    false    207    207            �
           1259    66564    car_pk    INDEX     ?   CREATE UNIQUE INDEX car_pk ON public.car USING btree (id_car);
    DROP INDEX public.car_pk;
       public            pi19    false    208            �
           1259    66565    color_pk    INDEX     G   CREATE UNIQUE INDEX color_pk ON public.color USING btree (name_color);
    DROP INDEX public.color_pk;
       public            pi19    false    210            �
           1259    66566    customer_lfp    INDEX     I   CREATE INDEX customer_lfp ON public.customer USING btree (lfp_customer);
     DROP INDEX public.customer_lfp;
       public            pi19    false    211            �
           1259    66567    customer_pk    INDEX     N   CREATE UNIQUE INDEX customer_pk ON public.customer USING btree (id_customer);
    DROP INDEX public.customer_pk;
       public            pi19    false    211            �
           1259    66568    do_fk    INDEX     @   CREATE INDEX do_fk ON public.booking USING btree (id_customer);
    DROP INDEX public.do_fk;
       public            pi19    false    205            �
           1259    66569    equipment_pk    INDEX     Q   CREATE UNIQUE INDEX equipment_pk ON public.equipment USING btree (id_equipment);
     DROP INDEX public.equipment_pk;
       public            pi19    false    213            �
           1259    66570    gets_fk    INDEX     B   CREATE INDEX gets_fk ON public.request USING btree (id_supplier);
    DROP INDEX public.gets_fk;
       public            pi19    false    219            �
           1259    66571 	   have_2_fk    INDEX     A   CREATE INDEX have_2_fk ON public.car USING btree (id_equipment);
    DROP INDEX public.have_2_fk;
       public            pi19    false    208            �
           1259    66572 	   have_3_fk    INDEX     C   CREATE INDEX have_3_fk ON public.equipment USING btree (id_model);
    DROP INDEX public.have_3_fk;
       public            pi19    false    213            �
           1259    66573    have_fk    INDEX     =   CREATE INDEX have_fk ON public.car USING btree (name_color);
    DROP INDEX public.have_fk;
       public            pi19    false    208            �
           1259    66574    located_in_2_fk    INDEX     I   CREATE INDEX located_in_2_fk ON public.car USING btree (number_booking);
 #   DROP INDEX public.located_in_2_fk;
       public            pi19    false    208            �
           1259    66575    located_in_fk    INDEX     C   CREATE INDEX located_in_fk ON public.car USING btree (id_request);
 !   DROP INDEX public.located_in_fk;
       public            pi19    false    208            �
           1259    66576    makes_out/contains_fk    INDEX     Q   CREATE INDEX "makes_out/contains_fk" ON public.request USING btree (id_manager);
 +   DROP INDEX public."makes_out/contains_fk";
       public            pi19    false    219            �
           1259    66577    makes_out_fk    INDEX     F   CREATE INDEX makes_out_fk ON public.booking USING btree (id_manager);
     DROP INDEX public.makes_out_fk;
       public            pi19    false    205            �
           1259    66578 
   manager_pk    INDEX     K   CREATE UNIQUE INDEX manager_pk ON public.manager USING btree (id_manager);
    DROP INDEX public.manager_pk;
       public            pi19    false    215            �
           1259    66579 	   models_pk    INDEX     G   CREATE UNIQUE INDEX models_pk ON public.models USING btree (id_model);
    DROP INDEX public.models_pk;
       public            pi19    false    217            �
           1259    66580 
   request_pk    INDEX     K   CREATE UNIQUE INDEX request_pk ON public.request USING btree (id_request);
    DROP INDEX public.request_pk;
       public            pi19    false    219            �
           1259    66581    supplier_pk    INDEX     N   CREATE UNIQUE INDEX supplier_pk ON public.supplier USING btree (id_supplier);
    DROP INDEX public.supplier_pk;
       public            pi19    false    221            �
           1259    66582 
   writes2_fk    INDEX     F   CREATE INDEX writes2_fk ON public.bill USING btree (number_boocking);
    DROP INDEX public.writes2_fk;
       public            pi19    false    203            �
           2606    66583 %   available fk_availabl_available_color    FK CONSTRAINT     �   ALTER TABLE ONLY public.available
    ADD CONSTRAINT fk_availabl_available_color FOREIGN KEY (name_color) REFERENCES public.color(name_color) ON UPDATE CASCADE ON DELETE CASCADE;
 O   ALTER TABLE ONLY public.available DROP CONSTRAINT fk_availabl_available_color;
       public          pi19    false    210    202    2788            �
           2606    66588 (   available fk_availabl_available_equipmen    FK CONSTRAINT     �   ALTER TABLE ONLY public.available
    ADD CONSTRAINT fk_availabl_available_equipmen FOREIGN KEY (id_equipment) REFERENCES public.equipment(id_equipment) ON UPDATE RESTRICT ON DELETE CASCADE;
 R   ALTER TABLE ONLY public.available DROP CONSTRAINT fk_availabl_available_equipmen;
       public          pi19    false    213    202    2796            �
           2606    66593    bill fk_bill_writes2_booking    FK CONSTRAINT     �   ALTER TABLE ONLY public.bill
    ADD CONSTRAINT fk_bill_writes2_booking FOREIGN KEY (number_boocking) REFERENCES public.booking(number_booking) ON UPDATE RESTRICT ON DELETE RESTRICT;
 F   ALTER TABLE ONLY public.bill DROP CONSTRAINT fk_bill_writes2_booking;
       public          pi19    false    205    203    2773            �
           2606    66598    booking fk_booking_do_customer    FK CONSTRAINT     �   ALTER TABLE ONLY public.booking
    ADD CONSTRAINT fk_booking_do_customer FOREIGN KEY (id_customer) REFERENCES public.customer(id_customer) ON UPDATE RESTRICT ON DELETE RESTRICT;
 H   ALTER TABLE ONLY public.booking DROP CONSTRAINT fk_booking_do_customer;
       public          pi19    false    211    205    2792            �
           2606    66603 $   booking fk_booking_makes_out_manager    FK CONSTRAINT     �   ALTER TABLE ONLY public.booking
    ADD CONSTRAINT fk_booking_makes_out_manager FOREIGN KEY (id_manager) REFERENCES public.manager(id_manager) ON UPDATE RESTRICT ON DELETE RESTRICT;
 N   ALTER TABLE ONLY public.booking DROP CONSTRAINT fk_booking_makes_out_manager;
       public          pi19    false    2799    215    205                        2606    66608 $   can_put fk_can_put_can_put2_supplier    FK CONSTRAINT     �   ALTER TABLE ONLY public.can_put
    ADD CONSTRAINT fk_can_put_can_put2_supplier FOREIGN KEY (id_supplier) REFERENCES public.supplier(id_supplier) ON UPDATE RESTRICT ON DELETE CASCADE;
 N   ALTER TABLE ONLY public.can_put DROP CONSTRAINT fk_can_put_can_put2_supplier;
       public          pi19    false    2809    207    221                       2606    66613 !   can_put fk_can_put_can_put_models    FK CONSTRAINT     �   ALTER TABLE ONLY public.can_put
    ADD CONSTRAINT fk_can_put_can_put_models FOREIGN KEY (id_model) REFERENCES public.models(id_model) ON UPDATE RESTRICT ON DELETE CASCADE;
 K   ALTER TABLE ONLY public.can_put DROP CONSTRAINT fk_can_put_can_put_models;
       public          pi19    false    2802    207    217                       2606    66618    car fk_car_have_2_equipmen    FK CONSTRAINT     �   ALTER TABLE ONLY public.car
    ADD CONSTRAINT fk_car_have_2_equipmen FOREIGN KEY (id_equipment) REFERENCES public.equipment(id_equipment) ON UPDATE RESTRICT ON DELETE RESTRICT;
 D   ALTER TABLE ONLY public.car DROP CONSTRAINT fk_car_have_2_equipmen;
       public          pi19    false    2796    208    213                       2606    66623    car fk_car_have_color    FK CONSTRAINT     �   ALTER TABLE ONLY public.car
    ADD CONSTRAINT fk_car_have_color FOREIGN KEY (name_color) REFERENCES public.color(name_color) ON UPDATE CASCADE ON DELETE RESTRICT;
 ?   ALTER TABLE ONLY public.car DROP CONSTRAINT fk_car_have_color;
       public          pi19    false    2788    208    210                       2606    66628    car fk_car_located_i_booking    FK CONSTRAINT     �   ALTER TABLE ONLY public.car
    ADD CONSTRAINT fk_car_located_i_booking FOREIGN KEY (number_booking) REFERENCES public.booking(number_booking) ON UPDATE RESTRICT ON DELETE RESTRICT;
 F   ALTER TABLE ONLY public.car DROP CONSTRAINT fk_car_located_i_booking;
       public          pi19    false    2773    208    205                       2606    66633    car fk_car_located_i_request    FK CONSTRAINT     �   ALTER TABLE ONLY public.car
    ADD CONSTRAINT fk_car_located_i_request FOREIGN KEY (id_request) REFERENCES public.request(id_request) ON UPDATE RESTRICT ON DELETE RESTRICT;
 F   ALTER TABLE ONLY public.car DROP CONSTRAINT fk_car_located_i_request;
       public          pi19    false    208    2806    219                       2606    66638 #   equipment fk_equipmen_have_3_models    FK CONSTRAINT     �   ALTER TABLE ONLY public.equipment
    ADD CONSTRAINT fk_equipmen_have_3_models FOREIGN KEY (id_model) REFERENCES public.models(id_model) ON UPDATE RESTRICT ON DELETE RESTRICT;
 M   ALTER TABLE ONLY public.equipment DROP CONSTRAINT fk_equipmen_have_3_models;
       public          pi19    false    2802    217    213                       2606    66643     request fk_request_gets_supplier    FK CONSTRAINT     �   ALTER TABLE ONLY public.request
    ADD CONSTRAINT fk_request_gets_supplier FOREIGN KEY (id_supplier) REFERENCES public.supplier(id_supplier) ON UPDATE RESTRICT ON DELETE RESTRICT;
 J   ALTER TABLE ONLY public.request DROP CONSTRAINT fk_request_gets_supplier;
       public          pi19    false    221    2809    219                       2606    66648 $   request fk_request_makes_out_manager    FK CONSTRAINT     �   ALTER TABLE ONLY public.request
    ADD CONSTRAINT fk_request_makes_out_manager FOREIGN KEY (id_manager) REFERENCES public.manager(id_manager) ON UPDATE RESTRICT ON DELETE RESTRICT;
 N   ALTER TABLE ONLY public.request DROP CONSTRAINT fk_request_makes_out_manager;
       public          pi19    false    215    219    2799            �   0  x�UR�N�@|��	w��b¯�h���&&5F_+����ș�aχK�ӝٙ��n��W�5V�]7�L��t��(
?�@O�YK��lM_�L��k&z����E�d���*��W�k����>���F�'��.�h��_@�(f��[y�h��uPҋJ����<�����+���H�C�(�glFv��H�ڜsKPn�v�*�K�vz`������Cd��F����_##��;��M��97l�/�
���� ��;��^�w�g�:J㰕�p���m ,^ٸ昬Yru�%�o��r��_j�hq      �   �   x���K� C��.S��k�2�?�dЦJ������DI�#D�z�=-�'��ZHHW�۵��g쨡�,�[Qgl�lC����c7����qן��Q���Q_rV�Z@Y���+��z�,�a�1:�
��+�@#�[�;h�t�9��D)=�_����]:�nvš���]Dg ��� �*:��d�w�ؤ�8�Ʊa�-��i�R      �   �   x�Mϱ�0C��E9��${��?G���q��+dsb��h�-�j5�5�5�`j�6��0�	����6��	�v��E�-{�q'�0�����L,/`�/�z�i�2�m��mj���o��U���O{���tO0      �   W   x��I@��Lj%�{p	Ih�D�T��Ѱ�9:\]�^��#�\���#���G>��?���,b�����R���d���~���      �   �  x���MN�0���)� �I�%��X�a��U�T��
 !� !�Bi!�6���F<�I�"uD�E��|3��suW�tAS��!}����]��4��F��I)����L�x�p��>���,5�X�i��
2J�!�*��o�b�膠k�Y�"Fd!��@J��w�"A7a/�;�j��$BI݀|uGk;��T(Ţ[�y��Ǩܤw߲;�O�-'I��+�fѝ����U]>ÚE��;n�+,ʲ��f�l?�J���P�<E��6�6Z;-]�T��e�\f1�.D���'R�FƢ'��3�noU#�Y�Lc���`�e�1��b���!L��}p�_}C��L:�2�B+֟Ln�Y�j�����̝y_�����@��k�*�#����,�(�mY5�N�i�q��H,M�Q&,z	^k����B��>�����.��֕�����t~ ���      �   �   x�e�]A���.�H�*�Bx �Dx]�o��+T�H��.���v�t}]=�!��Y�-�V�#M�#���	<'R�d7� h��\*6�X��Қ*/�5�͊��O���l.<��Iy3d�����\������FVq��\�\eUZ6I1�����\�~�[���xj����D��<�߬�E4�M�Ys?�l��s��=ku��ĥ�ɒ���e���(���}�C�����s/��L�      �   {  x�}U[n�0��N�"�����Hy� i��E� H��S@�-@�-�ay��"�~�?ɐ�g�CZ+m��(�y�JH���^؆�i1;�x���	���`o�-�iw��6��
7ݸ5L��H`$�g�7Rg���������r�3	�m�As�k{A;��P�4��^���sD����Z��R��BB��Z;G������*U*�b���L����M$s�*	��b���#&�Zŕs	y��>ٯ~�G�=&��:U����~B�t;�B��48��y��YQ�&/穄�Aq��P{;s;�h[L���5��0����o(�b�����MK�Ȳ{�#�&� ��L�8#�TMFB�����\��hIXa(�C���LB�5���~�����B��z.�a۲K8��<�;h��r��$�����t܍`Ohscf@�S3i�������� ���0�̂\�l�@��^�Hy�m�	鷽�>�9Vc8��%/�JBĭG�[���A��+L����s\{	���3������k8��/���o��!�▹A�J7�96�\�i$d\6��2�;��{w�b:O��B#��&�"�?^.ǦT:ϋ�(�|�j8d�:�>���ȩW>�^8��C�$Rc��      �   b  x�MR=o�@���r�\s����	T!�E����@��+�T� *����qI���l�;?[�
�Ԃ nҤ��\��h��P�����B����Qw�0k�D�:c��˺�C�!]�ढ़�)֡F{����y�h@�v"�ST�,���#/Q)��d��Z�"�Q>q╗� �-�A'��s�;�.\T�Fj�R��ʀr]�ا�ٹ}�������N%�F�@W�s�Sn����T�:IwG��Ϋ6@UmY�}�8�J9���i6D�Q�=q��Ж������'Nb�.�V��u-V�%�L���}SRWi)�K���w��1��@s�<��x_C�`��o      �   ?  x��T[n�@���'���&�.{ ���J��#Al�' �1g��Vw�cg�H��������iEi�#n�1u��s�Lbl���ӳ�(��
�ܥ�����ʚ��b��iGNTT���A�&�|�\�sڂ�p_%cŜ{�#4����еw3Q��a�df\���~��%`���jr��$�:�N}w@�@�����Jd%Tx��Q���[�/켨���/j��KC�S��4�I��Ҏ7���gF�� �|���}��/���2��R�\�Y�N�d��\ЏH]׺uQ0�W���H8�1�~ɑR��$�B�zL��ڇ����g,է�\���}�8�u ןXc;���W|7���h?��O����ul��&���)$\h�?�$3Y�|�!X��P7��۶h�p^c��n��W^��|���R;l��.�'l�Qo�����Et-�wH���� U�}1��k�7�e߼���yF�����[��TC;7���N��3�W�����woa��{��c�:��;g�m�lzn!Ezɋ���ZxC��fr08ͬ���t�������Qm�/'Q�m��      �   r  x�U��n�@��ç�����G[��V��F���#�������i���΀�-����щ2}�U+XC�$��r9*����OW�V�b����%G	�)�V�Vi��}�ѽ�B{�L�r�s�eK˔��pϮ�?5�PJ���x�����r�d�ؔ�0�$���`�׊��L������	�z;x\�՘�9�j-W�Ɗ-�Bf����[�;���2s|r�)!|�,�u�u��P~��Y�{Kί�\JY�V�Ex��[	�Q��1�2����;�v>�ؾ<[\�!m�[�p��'�g��;�^�֦���)�4Fv8rצ�~g�{W3�j}G����uЊ�J�b��*>��ߨ�>�"�D��      �   �   x�M���@C�3�K��f�%���:�����,�������Bǳ��9�΁���DNhr!'����<�	^�.��үm�x>)�Q);��RJy�&*�I[��m�R޴�J��.*�K����4���U�N��*�N��*�A��*��ߗ�<UY      �   �  x��TQO�P~��W�B���Gy0�4��Kٮ�����(<�1A4*H|�"������G~�v+�J����=_�������8}�]ҹܤ�`�W�S��1|1�S
�ۂaN0ڧ�� t�or]����w��o p@�AG��)B�5Er�.
�Uf3N�n�ъYh�ȶ�P(;�ë6"�z
�TfO�Ś�ौ�C
�G\�B
:2�=Z;�.�Ł�Qa�ϫ�rf?�C�Ι�6���%�N���۰���->���Ȑۚ�u����ᘎ�{�4�y/�%���p��UNBC\3�\�PiVټpk�.��i�Z�Ռ�O(8ԑ�-�VZXlz���H;ƹKt*��)�P+���i�C�.y�z���V�c7����7l�b3�>�p�̀����F�k�(�;xjG{�Z�M+��QK�i=~�����$����i�b���;x�D�B�A,�|�Ve}l�+쾿h�~
���;��g2�)��؜x�{)�ش��vɩBK3�A�\KJ��"���f�x������Ue�������!�����E�@xM���\��^�� *"��[�9�W{*�9��3��>�.u���f�%�v�5��G]sx5��l�nՍgE ��� ��Hv�p]�˲n��#����Г/(���zµ�V�;Vj �9��Ц�@0?ț���e�Q�����>P�o�ɎF��e��4��؂�Zܺ�UO���n<�U�������8��#H�.     